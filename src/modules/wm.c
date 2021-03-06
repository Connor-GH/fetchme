#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

/*
 * Thank you to Nyctanthous for the 
 * original version of this function
 */

int wm() {

    const char *supported_wm[] = {
        "fluxbox", "openbox", "blackbox",
        "xfwm4", "metacity", "kwin",
        "twin", "icewm", "pekwm", 
        "flwm", "flwm_topside", "fvwm",
        "dwm", "awesome", "wmaker",
        "stumpwm", "musca", "xmonad.*",
        "i3", "ratpoison", "scrotwm",
        "spectrwm", "wmfs", "wmii",
        "beryl", "subtle", "e16",
        "enlightenment", "sawfish", "emerald",
        "monsterwm", "dminiwm", "compiz",
        "Finder", "herbstluftwm", "howm",
        "notion", "bspwm", "cinnamon",
        "2bwm", "echinus", "swm",
        "budgie-wm", "dtwm", "9wm",
        "chromeos-wm", "deepin-wm", "sway",
        "mwm" 
    }; // this system is fragile but works very well

        FILE *fp = popen("ps aux", "r");
        if (fp == NULL) { 
            printf("\033[1;31mDo you not have `ps'?\033[0m\n");
            return -1;
        }
        char lookup[128];

        while (fgets(lookup, sizeof(lookup) - 1, fp) != NULL) {

            for(int i = 0; i < 49; i++) {

                if(strstr(lookup, supported_wm[i]) != NULL) {

                    printf(COLOR);
                    printf("WM:\033[0m %s\n", supported_wm[i]);
                    pclose(fp);
                    return 0;
                }
            }
        }

    pclose(fp);

    printf("\033[1;31mYour WM was not found\033[0m\n");
    return -1;
}
