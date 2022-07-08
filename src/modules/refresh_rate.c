#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "./include/refresh_rate.h"

int refresh_rate() {
    Display *display = XOpenDisplay(NULL);
    Window default_root_window = XDefaultRootWindow(display);

    XRRScreenResources *screen_resources = \
    XRRGetScreenResources(display, default_root_window);

    RRMode active_mode_id = 0;
    
    for(int i = 0; i < screen_resources->ncrtc; ++i) {
        XRRCrtcInfo *crtc_info = \
        XRRGetCrtcInfo(display, \
            screen_resources, screen_resources->crtcs[i]);

        if (crtc_info->mode != None) {
            active_mode_id = crtc_info->mode;
        }
        // i hate X11 C library for being overall awful
        XRRFreeCrtcInfo(crtc_info);
    }

    double active_rate = 0;

    for (int i = 0; i < screen_resources->nmode; ++i) {
        XRRModeInfo mode_info = screen_resources->modes[i];
        if (mode_info.id == active_mode_id) {
            active_rate = (double)mode_info.dotClock / \
            ((double)mode_info.hTotal * (double)mode_info.vTotal);
        }
    }

    printf(" %.2fHz\n", active_rate);

    XCloseDisplay(display);
    XRRFreeScreenResources(screen_resources);
    
    return 0;
}
