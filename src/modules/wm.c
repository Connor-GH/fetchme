#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#ifdef WAYLAND
#include <string.h>
#else
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#endif

#include "./include/fetchme.h"
#ifndef WAYLAND

static inline Window *
list(Display *disp, unsigned long *len)
{
	Atom prop = XInternAtom(disp, "_NET_SUPPORTING_WM_CHECK", False), type;
	int form;
	unsigned long remain;
	unsigned long *list;

	XGetWindowProperty(disp, XDefaultRootWindow(disp), prop, 0, 1024, False,
					   XA_WINDOW, &type, &form, len, &remain,
					   (unsigned char **)&list);
	return (Window *)list; // this has to be a Window * for when we run `name'
}

static inline char *
name(Display *disp, Window window)
{
	Atom prop = XInternAtom(disp, "_NET_WM_NAME", False), type;
	int form;
	unsigned long remain, len;
	unsigned char *list;

	XGetWindowProperty(disp, window, prop, 0, 1024, False, AnyPropertyType,
					   &type, &form, &len, &remain, &list);
	return (char *)list;
}

#endif /* ifndef WAYLAND */

int
wm(const char *color_distro)
{
#if UNIX_SUPPORT
	/*
     *  Use the traditional method to get
     *  window managers other than
     *  ones based on X11
     */
#ifdef WAYLAND
	char lookup[128];
	const char *const supported_wm[22] = {
		"xfwm4",	 "metacity", "kwin",	  "twin", "musca",
		"scrotwm",	 "beryl",	 "subtle",	  "e16",  "emerald",
		"monsterwm", "dminiwm",	 "Finder",	  "howm", "notion",
		"2bwm",		 "echinus",	 "budgie-wm", "dtwm", "chromeos-wm",
		"deepin-wm", "sway"

	}; // this system works as a backup to the X11 detection

	FILE *fp = popen("ps x", "r");
	if (fp == NULL) {
		fprintf(stderr, "Do you not have `ps'?\n");
		return EXIT_FAILURE;
	}
	while (fgets(lookup, sizeof(lookup) - 1, fp) != NULL) {
		for (int i = 0; i < 21; i++) {
			if (strstr(lookup, supported_wm[i]) != NULL) {
				pclose(fp);

				printf("%sWM:\033[0m %s\n", color_distro, supported_wm[i]);
				return EXIT_SUCCESS;
			}
		}
	}

	pclose(fp);

	fprintf(stderr, "Your WM was not found\n");
	return EXIT_FAILURE;
#endif /* ifdef WAYLAND */

#ifndef WAYLAND
	Display *disp = XOpenDisplay(NULL);
	unsigned long len;
	Window *wlist = (Window *)list(disp, &len);
	char *wname = name(disp, wlist[0]);

	XFree(wlist);
	printf("%sWM:\033[0m %s\n", color_distro, wname);
	free(wname);

	XCloseDisplay(disp);
	return EXIT_SUCCESS;
#endif /* ifndef WAYLAND */
#else
	return EXIT_SUCCESS;
#endif
}
