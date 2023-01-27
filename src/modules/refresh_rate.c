#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "./include/fetchme.h"

int
refresh_rate(const char *color_distro)
{
#if UNIX_SUPPORT
	double active_rate = 0;
	Display *display = XOpenDisplay(NULL);
	Window default_root_window = XDefaultRootWindow(display);

	/*
     * XRRGetScreenResourcesCurrent was introduced in XRandr 1.3.
     * It increases refresh rate detection performance by about 23 times
     * versus XRRGetScreenResources.
     */
	XRRScreenResources *screen_resources =
		XRRGetScreenResourcesCurrent(display, default_root_window);

	RRMode active_mode_id = 0;

	for (int i = 0; i < screen_resources->ncrtc; ++i) {
		XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(display, screen_resources,
												screen_resources->crtcs[i]);

		if (crtc_info->mode != None) {
			active_mode_id = crtc_info->mode;
		}
		XRRFreeCrtcInfo(crtc_info);
	}

	for (int i = 0; i < screen_resources->nmode; ++i) {
		XRRModeInfo mode_info = screen_resources->modes[i];
		if (mode_info.id == active_mode_id) {
			active_rate = (double)mode_info.dotClock /
						  ((double)mode_info.hTotal * (double)mode_info.vTotal);
		}
	}

#ifdef RESOLUTION
	printf(" %.2fHz\n", active_rate);
#else
	printf("%sRefresh Rate: \033[0m%.2fHz\n", color_distro, active_rate);
#endif

	XCloseDisplay(display);
	XRRFreeScreenResources(screen_resources);

#endif
	return EXIT_SUCCESS;
}
