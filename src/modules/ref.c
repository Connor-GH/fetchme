#include <xcb/randr.h>
#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/fetchme.h"

/*
 * screen_of_display was taken from xcb's translation page:
 * https://xcb.freedesktop.org/xlibtoxcbtranslationguide/
 */
static xcb_screen_t *
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
refresh_rate(const char *color_distro)
{
#if UNIX_SUPPORT
	xcb_connection_t *connection;
	xcb_randr_get_screen_info_cookie_t screen_info;
	xcb_randr_get_screen_info_reply_t *reply; /* we need to fill reply->rate */
	int screen_num;
	xcb_screen_t *screen;

	/* Connect xcb display */
	connection = xcb_connect(":0", &screen_num);

	/* initialize the screen */
	screen = screen_of_display(connection, screen_num);

	if (!screen) {
		fprintf(stderr, "Screen not found.");
		exit(EXIT_FAILURE);
	}

	/* xcb needs to know you are using xcb 1.1 or above */
	xcb_randr_query_version(connection, 1, 1);

	/* get the info required for refresh rate */
	screen_info = xcb_randr_get_screen_info_unchecked(connection, screen->root);
	reply = xcb_randr_get_screen_info_reply(connection, screen_info, NULL);

#ifdef RESOLUTION
	printf(" %dHz\n", reply->rate);
#else
    printf("%sRefresh Rate: %dHz\n", color_distro, reply->rate);
#endif

#endif
	return EXIT_SUCCESS;
}
