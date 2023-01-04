#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include "./include/fetchme.h"

int
resolution(const char *color_distro)
{
#if UNIX_SUPPORT
	Display *d;
	int width = 0;
	int height = 0;

	if (!(d = XOpenDisplay(NULL))) {
		fprintf(stderr, "cannot open display '%s'\n", XDisplayName(0));
		exit(EXIT_FAILURE);
	}

	width = DisplayWidth(d, DefaultScreen(d));
	height = DisplayHeight(d, DefaultScreen(d));

	XCloseDisplay(d);

	printf("%sResolution:\033[0m %dx%d", color_distro, width, height);
#ifdef REFRESH_RATE
	/*
     * Comment or uncomment the define line
     * in config.mk for refresh rate
     */
	printf(" @");
#else
	printf("\n");
#endif
#endif
	return EXIT_SUCCESS;
}
