#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/utsname.h>

#include "./include/distro.h"
#include "./include/config.h"
#include "./include/color.h"

 int distro() {
    struct utsname buffer;

    char os_name[50];

    errno = 0;
    if (uname(&buffer) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    FILE *os_release = fopen("/etc/os-release", "r");

    if(os_release == NULL) {
        printf("OS release NULL\n");
        exit(EXIT_FAILURE);
    }

    fscanf(os_release, "NAME=%49[^\n]+", os_name);  // get everything
                                                    // that isn't a
                                                    // newline
    fclose(os_release);
    /*
     * remove quotation marks from
     * os name if needed.
     */
        sscanf(os_name, "\"%49[^\"]+", os_name);
        printf(COLOR);
        printf("OS:\033[0m %s %s\n", \
                os_name, buffer.machine);



    return EXIT_SUCCESS;
}
