#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <err.h>

#include "./include/color.h"
#include "./include/config.h"
#include "./include/fetchme.h"

int resolution() {

    Display *d;

    if(!(d = XOpenDisplay(NULL)))
        errx(1, "cannot open display '%s'\n", XDisplayName(0));

    int width  = DisplayWidth (d, DefaultScreen(d));
    int height = DisplayHeight(d, DefaultScreen(d));

    XCloseDisplay(d);

    printf(COLOR);
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
