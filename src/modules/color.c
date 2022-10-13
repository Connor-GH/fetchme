#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/color.h"

const char *
color_distro()
{
	char os_name[50];
	FILE *os_release = fopen("/etc/os-release", "r");

	if (os_release == NULL) {
		perror("/etc/os-release");
		exit(EXIT_FAILURE);
	}

	fscanf(os_release, "NAME=%49[^\n]+", os_name); /* get everything
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
	if (strcmp(os_name, "Gentoo") == 0) {
		return PURPLE;
	} else if (strncmp(os_name, "Debian", 6) == 0) {
		return RED;
	} else if (strncmp(os_name, "Void", 4) == 0) {
		return "\033[1;38;5;34m";
	} else if (strncmp(os_name, "Ubuntu", 6) == 0) {
		return "\033[1;38;5;202m";
	} else if (strncmp(os_name, "Solus", 5) == 0) {
		return BLUE;
	} else if (strncmp(os_name, "Alpine", 6) == 0) {
		return PURPLE;
	} else if ((strncmp(os_name, "Pop!_OS", 7)) ||
            (strncmp(os_name, "popos", 5)) ||
            (strncmp(os_name, "pop_os", 6)) == 0) {
		return "\033[1;38;5;29m";
	} else if ((strncmp(os_name, "Mint", 4)) ||
            (strncmp(os_name, "OpenSUSE", 8)) ||
            (strncmp(os_name, "openSUSE", 8)) ||
            (strncmp(os_name, "Manjaro", 7)) == 0) {
		return GREEN;
	} else if ((strncmp(os_name, "Arch", 4)) ||
			   (strncmp(os_name, "Artix", 5)) == 0) {
		return CYAN;
	} else {
		fprintf(stderr, "Exception: distro color not found.");
		exit(EXIT_FAILURE);
	}
#endif
#ifdef CUSTOM_COLOR
	return CUSTOM_COLOR_VALUE;
#endif
}
