#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

int package_count() {
    size_t count = 0;
    struct stat sb;
    /* you can do a case statement around *path
     * if you want to get other distros' package counts
     */
    const char *path = "/var/lib/pacman/local";

    // this is an awful amount of tabs and if statements

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    DIR *folder = opendir(path);

        if (access (path, F_OK) != -1 ) {
            if (folder) {
                struct dirent *res;
                while ((res = readdir(folder))) {
                    if (strcmp(res->d_name, ".") && strcmp(res->d_name, ".." )) {
                        count++;
                    }
                }

                closedir(folder);
            }
            else {
                perror ("Could not open the directory");
                exit(EXIT_FAILURE);
            }
        }
   }
    else {
        printf("The %s it cannot be opened or is not a directory\n", path);
        exit (EXIT_FAILURE);
    }
    printf(COLOR);
    printf("Packages:\033[0m %zu\n", count-1);
    return 0;
}
