#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>

#include "./include/fetchme.h"
#include "./include/color.h"

 int distro() {
    struct utsname buffer;

    char os_name[50];
    char info_desc[20];

    FILE *os_release = fopen("/etc/os-release", "r");

    if (uname(&buffer) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    if(os_release == NULL) {
        perror("/etc/os-release");
        exit(EXIT_FAILURE);
    }

    while (fgets(os_name, sizeof os_name, os_release) != NULL) {

        sscanf(os_name, "%19[^=]=\"%49[^\"]", info_desc, os_name);
        if (strcmp(info_desc, "PRETTY_NAME") == 0) { 

            fclose(os_release);
            printf("%sOS:\033[0m %s %s\n", \
                color_distro(), os_name, buffer.machine);
            return EXIT_SUCCESS;
        }
    }
    fclose(os_release);
    fprintf(stderr, "Distro name not found.\n");

    ////fscanf(os_release, "NAME=%49[^n]+", os_name);  // get everything
                                                    // that isn't a
                                                    // newline
    ////fclose(os_release);
    /*
     * remove quotation marks from
     * os name if needed.
     */
       //// sscanf(os_name, "\"%49[^\"]+", os_name);

       //// printf("%sOS:\033[0m %s %s\n", \
                color_distro(), os_name, buffer.machine);



    return EXIT_FAILURE/*SUCCESS*/;
}
