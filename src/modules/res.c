#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/fetchme.h"
#include "include/color.h"

xcb_screen_t *
screen_of_display(xcb_connection_t *c, int screen)
{
	xcb_screen_iterator_t iter;

	iter = xcb_setup_roots_iterator(xcb_get_setup(c));
	for (; iter.rem; --screen, xcb_screen_next(&iter))
		if (screen == 0)
			return iter.data;

	return NULL;
}

int
resolution(void)
{
	xcb_connection_t *c;
	xcb_screen_t *screen;
	int screen_nbr = 0;
	uint16_t width;
	uint16_t height;

	c = xcb_connect(":0", &screen_nbr);
	screen = screen_of_display(c, screen_nbr);

	if (screen) {
		width = screen->width_in_pixels;
		height = screen->height_in_pixels;
	} else {
		fprintf(stderr, "Screen not found.\n");
		exit(EXIT_FAILURE);
	}
	printf("%sResolution:\033[0m %dx%d", color_distro(), width, height);
#ifdef REFRESH_RATE
	/*
     * Comment or uncomment the define line
     * in config.mk for refresh rate
     */
	printf(" @");
#else
	printf("\n");
#endif

	return EXIT_SUCCESS;
}
