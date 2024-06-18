/*
-----------------------------------------------
Basic start up code.
-----------------------------------------------
*/

/*!
\mainpage <TITULO DO PROGRAMA>
\author Heitor Adão Junior
\image html logo.png

Esse programa foi desenvolvido com o objetivo de ...

Este manual é dividido nas seguintes seções:
- \subpage intro "Introdução e Justificativa sobre o programa"
- \subpage ferramentas "Tecnologias e ferramentas utilizadas"
- \subpage logica "Lógica do programa"
*/

/*! \page intro "Introdução e Justificativa sobre o programa"
This page introduces the user to the topic.
Now you can proceed to the \ref ferramentas "Tecnologias e ferramentas utilizadas".
*/

/*! \page ferramentas "Tecnologias e ferramentas utilizadas"
This page is for advanced users.
Make sure you have first read \ref intro "Introdução sobre o programa".
*/

/*! \page logica "Lógica do programa"
This page is for advanced users.
Make sure you have first read \ref intro "Introdução sobre o programa".
*/





#include <allegro.h>

#include "error.h"		// error reporting
#include "kernel.h"	// main game loop
#include "menu.h"       // menu principal


/*!
\brief Program entry point
*/
int main(int argc, char *argv[])
{
	// GFX_AUTODETECT_FULLSCREEN
	int vid_m = GFX_AUTODETECT_WINDOWED;	// screen desired graphic mode
	int game_color_depth = 32;				// desired screen color depth
	int vid_w = 640;						// desired video resolution
	int vid_h = 480;

	/* check command line parameters */
	for (int i = 1; i < argc; i++)
	{
		//if (stricmp(argv[i], "-wn") == 0) vid_m = GFX_AUTODETECT_WINDOWED;
	}

	allegro_init();
	set_uformat(U_ASCII);	// Permite usar acentos da língua portuguesa.
	srand(time(NULL));		// init seed random numbers

	if (install_timer())
		raise_error("main() : can't install timer driver");

	if (install_keyboard())
		raise_error("main() : can't install keyboard driver");

	if (install_mouse() < 0)
		raise_error("main() : can't install mouse driver");

	/* ---------------------
	here you can init other hardware, such as sound, joystick, etc

	example(s):

	reserve_voices( digi_voices, midi_voices);
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) ) raise_error("install_sound() failed.\n'%s'\n", allegro_error);
	set_volume_per_voice(scale);

	install_joystick(JOY_TYPE_AUTODETECT);
	----------------------- */

	/* set graphics mode */
	set_color_depth(game_color_depth);
	if (set_gfx_mode(vid_m, vid_w, vid_h, 0, 0))
		raise_error("main() : I can't set the graphics mode (%3d x %3d @ %2d bpp)", vid_w, vid_h, game_color_depth);





	//----------------------------------------
	//          Aqui começa o menu
	//----------------------------------------

	CMenu *menuPrincipal = new CMenu;
	menuPrincipal->Init();
	menuPrincipal->Draw();
	int tecla = 0;
	bool sair = false;
	while (!sair)
	{
		while(!keypressed());
		while(keypressed())
			tecla = readkey();
		if (tecla >> 8 == KEY_ENTER)
		{
			switch(menuPrincipal->focus)
			{
			case 0:
				gkernel_init(); // start the game kernel and main game loop (located at gkernel.cpp)
				menuPrincipal->Draw();
				break;
			case 1:
				// options
				break;
			case 2:
				sair = true;
				break;
			}
		}
		if (tecla >> 8 == KEY_UP)
		{
			menuPrincipal->FocusUp();
			menuPrincipal->Draw();
		}
		if (tecla >> 8 == KEY_DOWN)
		{
			menuPrincipal->FocusDown();
			menuPrincipal->Draw();
		}
	}
	delete menuPrincipal;
	return 0;			// normal end of the program
}
END_OF_MAIN()
