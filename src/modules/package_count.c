#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#if defined(__linux__)
#include <glob.h>
#endif
#include <stdio.h>
#include "./include/fetchme.h"
#include "./include/color.h"

int
package_count()
{
	size_t PKG_COUNT = 0;

#if defined(__linux__)
	glob_t globbuf;
	if ((glob("/var/lib/pacman/local/*", GLOB_NOSORT, NULL,
			 &globbuf) == 0)            // arch-based
    || (glob("/var/db/pkg/*/*", GLOB_NOSORT, NULL,
					&globbuf) == 0)) {  // portage-based
		PKG_COUNT = globbuf.gl_pathc;

	} else {
		fprintf(stderr, "No packages found\n");
		exit(EXIT_FAILURE); // die, no directories work
	}
#endif /* Linux */

#if defined(__FreeBSD__)
	// pkg-based
	FILE *fp = popen("pkg info", "r");
	char lookup[128];
	if (fp == NULL) {
		perror("pkg");
		exit(EXIT_FAILURE);
	}

	while (fgets(lookup, sizeof(lookup) - 1, fp) != NULL) {
		PKG_COUNT++;
	}
	pclose(fp);
#endif /* FreeBSD */

	printf("%sPackages:\033[0m %lu\n", color_distro(), PKG_COUNT);
#if defined(__linux__)
	globfree(&globbuf);
#endif
	return EXIT_SUCCESS;
}
