#ifndef CUSTOM_COLOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "include/color.h"
#include "include/fetchme.h"
const char *
color_distro(void)
{
#if UNIX_SUPPORT
#ifndef CUSTOM_COLOR
#define AMOUNT_DISTROS 17
	char os_name[64];
	int c;
	int file = 0;
	FILE *os_release = fopen("/etc/os-release", "r");

	const char *const supported_distros[AMOUNT_DISTROS] = {
		"Gentoo",  "Debian",  "Void",  "Ubuntu",   "Solus",	   "Alpine",
		"Mint",	   "Arch",	  "Artix", "OpenSUSE", "openSUSE", "Manjaro",
		"FreeBSD", "OpenBSD", "popos", "pop_os",   "Pop!_OS"
	};

	const char *const distro_colors[AMOUNT_DISTROS] = { PURPLE,
														RED,
														"\033[1;38;5;34m",
														"\033[1;38;5;202m",
														BLUE,
														PURPLE,
														GREEN,
														CYAN,
														CYAN,
														GREEN,
														GREEN,
														GREEN,
														RED,
														YELLOW,
														"\033[1;38;5;29m",
														"\033[1;38;5;29m",
														"\033[1;38;5;29m" };

	const unsigned long distro_length[AMOUNT_DISTROS] = { 6, 6, 4, 6, 5, 6,
														  4, 4, 5, 8, 8, 7,
														  7, 7, 5, 6, 7 };

	if (os_release == NULL) {
		perror("/etc/os-release");
		exit(EXIT_FAILURE);
	}
	fscanf(os_release, "%63[^=]=", os_name);

	while ((file != EOF) && (strncmp(os_name, "NAME", 11) != 0)) {
		while ((c = fgetc(os_release)) != '\n' && c != EOF)
			;
		file = fscanf(os_release, "%63[^=]=", os_name);
	}

	if (file == EOF)
		exit(EXIT_FAILURE);

	fscanf(os_release, "%63[^\n]+", os_name); /* get everything
                                                     * that isn't a
                                                     * newline */

	fclose(os_release);
	/*
     * remove quotation marks from
     * os name if needed.
     */
	sscanf(os_name, "\"%[^\"]", os_name);
	/* Iterate arrays of distro info. If one is right, return it. */

	for (int i = 0; i < AMOUNT_DISTROS; i++) {
		if (strncmp(os_name, supported_distros[i], distro_length[i]) == 0)
			return distro_colors[i];
	}
	fprintf(stderr, "Exception: distro color not found.");
	exit(EXIT_FAILURE);
#endif
#ifdef CUSTOM_COLOR
	return CUSTOM_COLOR_VALUE;
#endif
#else
	return WHITE;
#endif
}
