#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/color.h"

const char *
color_distro() 
{
    char os_name[50];
    const char *COLOR = 0;
    FILE *os_release = fopen("/etc/os-release", "r");


    if(os_release == NULL) {
        perror("/etc/os-release");
        exit(EXIT_FAILURE);
    }

    fscanf(os_release, "NAME=%49[^\n]+", os_name);  /* get everything
                                                         * that isn't a
                                                         * newline */
    fclose(os_release);
    /*
     * remove quotation marks from
     * os name if needed.
     */
    sscanf(os_name, "\"%[^\"]", os_name); // get everything that isn't quotes
        /* if statement for distro name */
#ifndef CUSTOM_COLOR
    if (strstr(os_name, "Gentoo") != NULL) COLOR = PURPLE;
    else if (strstr(os_name, "Debian") != NULL) COLOR = RED;
    else if (strstr(os_name, "Void") != NULL) COLOR = "\033[1;38;5;34m";
    else if (strstr(os_name, "Ubuntu") != NULL) COLOR = "\033[1;38;5;202m";
    else if (strstr(os_name, "Solus") != NULL) COLOR = BLUE;
    else if ((strstr(os_name, "Pop!_OS")) \
            || (strstr(os_name, "popos")) \
            || (strstr(os_name, "pop_os")) != NULL) COLOR = "\033[1;38;5;29m";
    else if ((strstr(os_name, "Mint")) \
            || (strstr(os_name, "OpenSUSE")) \
            || (strstr(os_name, "openSUSE")) \
            || (strstr(os_name, "Manjaro")) != NULL) COLOR = GREEN;
    else if ((strstr(os_name, "Arch")) \
            || (strstr(os_name, "Artix")) != NULL) COLOR = CYAN;
    else { 
        fprintf(stderr, "Exception: distro color not found.");
        exit(EXIT_FAILURE); // return value is 1
    }
#endif
#ifdef CUSTOM_COLOR
    COLOR = CUSTOM_COLOR_VALUE;
#endif

return COLOR;
}
