/*
-----------------------------------------------
Error messages
-----------------------------------------------
*/
#ifndef GERROR_C
#define GERROR_C

#include "error.h"


/*!
\brief Goes back to text mode, shows the message and ends the program.
*/
void raise_error(AL_CONST char *msg, ...)
{
	char	*buf;

	/* exits the graphics mode */
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

	/* creates the buffer */
	buf = (char *) malloc(4096);
	if (buf == NULL)
	{
		allegro_message("raise_error(): There is a error, and I'm out of virtual memory to show the error message. :^(\n");
	}
	else
	{
		/* parse the variable parameters */
		va_list ap;

		va_start(ap, msg);
		uvszprintf(buf, 4096, msg, ap);
		va_end(ap);

		allegro_message("%s\n", buf);
		free(buf);
	}
	exit(1);	/* abort the program */
}
#endif
