#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>

#include "./include/fetchme.h"
#include "./include/color.h"


int
package_count() 
{
    glob_t globbuf;

    if (glob("/var/lib/pacman/local/*", GLOB_NOSORT, NULL, &globbuf) != 0) // arch-based
        glob("/var/db/pkg/*/*", GLOB_NOSORT, NULL, &globbuf); // portage-based
    else 
        exit(EXIT_FAILURE); // die, no directories work

    printf("%sPackages:\033[0m %lu\n", \
            color_distro(), globbuf.gl_pathc);
    globfree(&globbuf);
    return 0;
}
