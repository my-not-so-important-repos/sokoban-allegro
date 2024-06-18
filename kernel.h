/*
-----------------------------------------------
Game main loop and kernel
-----------------------------------------------
*/

#ifndef GKERNEL_H
#define GKERNEL_H

#include <allegro.h>
#include "error.h"
#include "cenario.h"

#define UL_CONTINUE     0
#define UL_PLAYER_EXIT  1
#define UL_PLAYER_WIN   2
#define UL_PLAYER_LOSE  3
#define UL_TIME_OVER    4

void gkernel_init();
int gkernel_update_logic(CCenario*);
void gkernel_update_screen(CCenario*);
#endif

