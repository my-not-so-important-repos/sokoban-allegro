/*
-----------------------------------------------
Game main loop and kernel
-----------------------------------------------
*/

#include "kernel.h"


#define FPSQ	30	/* timer update ratio, in BPS */

/* Game Over? */
int				game_over = FALSE;

/* Counter for the main timer */
volatile int	speed_counter = 0;
volatile int    gClock = 0;

/* this 2 counters are for count the fps */
volatile int	frame_count, fps;


/* Timer callback for the speed counter */
void increment_speed_counter()
{
	speed_counter++;
	gClock++;
}
END_OF_FUNCTION(increment_speed_counter);


/* Timer callback for measuring the frames per second */
void fps_proc(void)
{
	fps = frame_count;
	frame_count = 0;
}
END_OF_FUNCTION(fps_proc);


/*!
\brief Kernel start up.
Here you should also init all your game, and all stuff
You may prefer to load datafiles in main.c or other place,
before comin' here.
*/
void gkernel_init()
{
	/* set the timer */
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);

	LOCK_VARIABLE(fps);
	LOCK_VARIABLE(frame_count);
	LOCK_FUNCTION(fps_proc);

	/* install the timer */
	if (install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPSQ)))
		raise_error("gkernel_init() : Can't install timer at %d bps\n", FPSQ);
	if (install_int(fps_proc, 1000))
		raise_error("gkernel_init() : Can't install timer to measure fps.");

	/* here start all the variables and all stuff */
	CCenario *cenario = new CCenario;
	cenario->Init("level1.txt", "res/tileset.bmp");
	cenario->heroi->hClock = &gClock;

	game_over = FALSE;
	frame_count = fps = 0;

	/* Main game loop */
	while (!game_over)
	{
		while (speed_counter > 0)
		{
			if (gkernel_update_logic(cenario) == UL_PLAYER_EXIT)
                game_over = TRUE;
			speed_counter--;
		}
		gkernel_update_screen(cenario);	/* update screen */
		frame_count++;			        /* count fps */
	}

	/* end of main game loop */

	/* remove timer(s) */
	remove_int(increment_speed_counter);
	remove_int(fps_proc);

	/* NOTE: HERE YOU SHOULD FREE THE RAM USED, ETC, HERE THE GAME FINISHED... */
}


/*!
\brief Updates the game logic.
*/
int gkernel_update_logic(CCenario* cenario)
{
    if (key[KEY_ESC])
        return UL_PLAYER_EXIT;
    if (key[KEY_RIGHT])
        cenario->MoveRight();
    if (key[KEY_LEFT])
        cenario->MoveLeft();
    if (key[KEY_UP])
        cenario->MoveUp();
    if (key[KEY_DOWN])
        cenario->MoveDown();
    return UL_CONTINUE;
}


/*!
\brief Updates the graphics
*/
void gkernel_update_screen(CCenario* cenario)
{
    static BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *imagemCenario = cenario->DrawAll();
    clear_to_color(buffer, makecol(0, 0, 0));
    blit(imagemCenario, buffer, 0, 0, 0, 32, imagemCenario->w, imagemCenario->h);
	textprintf_ex(buffer, font, 0, 0, makecol(255, 255, 255), -1, "Hit <ESC> to quit - %5d fps", fps);
	textprintf_ex(buffer, font, 0, 8, makecol(255, 255, 255), -1, "speed_counter = %5d", speed_counter);
	textprintf_ex(buffer, font, 0, 16, makecol(255, 255, 255), -1, "kernel clock = %5d", gClock);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
