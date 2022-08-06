#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <err.h>

#include "./include/color.h"
#include "./include/fetchme.h"

int resolution() {

    Display *d;
    int width = 0;
    int height = 0;

    if(!(d = XOpenDisplay(NULL)))
        errx(1, "cannot open display '%s'\n", XDisplayName(0));

    width  = DisplayWidth (d, DefaultScreen(d));
    height = DisplayHeight(d, DefaultScreen(d));

    XCloseDisplay(d);

    printf("%s", color_distro());
    printf("Resolution:\033[0m %dx%d", width, height); 
#ifdef REFRESH_RATE
    /* 
     * Comment or uncomment the define line 
     * in config.h for refresh rate
     */
    printf(" @"); 
#else
    printf("\n"); 
#endif
    return 0;
}
