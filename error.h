/*
-----------------------------------------------
Error messages
-----------------------------------------------
*/

#ifndef GERROR_H
#define GERROR_H

#include <allegro.h>
#include <stdarg.h> /* for the variable argument list */
#include <stdlib.h> /* for use of malloc */
void raise_error(AL_CONST char *msg, ...);

#endif
