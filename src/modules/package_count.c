//#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include "./include/fetchme.h"

#if LINUX_SUPPORT_ONLY
#include <glob.h>
#endif

int
package_count(const char *color_distro)
{
	size_t PKG_COUNT = 0;

#if LINUX_SUPPORT_ONLY
	glob_t globbuf;
    FILE *fp;
	if ((glob("/var/lib/pacman/local/*", GLOB_NOSORT, NULL,
			  &globbuf) == 0) // arch-based
		|| (glob("/var/db/pkg/*/*", GLOB_NOSORT, NULL,
				 &globbuf) == 0)) { // portage-based
		PKG_COUNT = globbuf.gl_pathc;

	} else if ((fp = fopen("/lib/apk/db/installed", "r")) != NULL) {
        char buf[64];
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            if (*buf == 'P')
                PKG_COUNT++;
        }
        fclose(fp);
    } else {
		fprintf(stderr, "No packages found\n");
		exit(EXIT_FAILURE); // die, no directories work
	}
#endif /* Linux */

#if BSD_SUPPORT_ONLY
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

	printf("%sPackages:\033[0m %lu\n", color_distro, PKG_COUNT);
#if LINUX_SUPPORT_ONLY
	globfree(&globbuf);
#endif
	return EXIT_SUCCESS;
}
