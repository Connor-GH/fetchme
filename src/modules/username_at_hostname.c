#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

 int username_at_hostname() {
        char hostname_value[100];
        uid_t  uid;
        struct passwd *pwd;
        char line[200];            /* Accounts for user 'foo',
                                    * hostname 'bar', and the '+1'
                                    * accounts for the @ symbol.
                                    *
                                    * This is fine as long as 
                                    * the username is not 101
                                    * bytes long. (this "fixes" a VLA) */

        FILE *host = fopen("/etc/hostname", "r");
        if(host == NULL) {
                printf("No hostname found, exiting...\n");
                exit(EXIT_FAILURE);
        }
        fscanf(host, "%99s", hostname_value);

        fclose(host);

        if ((pwd = getpwuid(uid = geteuid())) == NULL) {
            perror("getpwuid() error");
            exit(EXIT_FAILURE);
        }

        /* if this fails, we know that
         * username is a sane size */
        if (strlen(pwd->pw_name) >= 100) { 
            perror("Username too long.");
            printf("Username is %lu bytes, expected less than "
                    "or equal to 100 bytes.\n", strlen(pwd->pw_name));
            exit(EXIT_FAILURE);
        }
        else {
            printf(COLOR);
            printf("%s\033[0m@", pwd->pw_name);
            printf(COLOR);
            printf("%s\033[0m\n", hostname_value);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-compare"
    /*
     * explanation for pragma:
     * pwd->pw_name and hostname_value have been 
     * error checked to confirm they are under 100 bytes
     * for the hostname, and under 101 bytes for the username.
     * with the max of 199 bytes, it is not actually not large
     * enough to warrant an unsigned long. strlen is declared
     * as a `size_t', which is an unsigned long by the C standard,
     * and thus returns one. this is no issue here.
     */
            for (int i= 0; i < (strlen(pwd->pw_name) + strlen(hostname_value)+1); i++) line[i] = '~';
#pragma clang diagnostic pop
            line[(strlen(pwd->pw_name) + strlen(hostname_value)+1)] = '\0';

            printf(COLOR);
            printf("%s\033[0m\n", line);
    }
    return EXIT_SUCCESS;

}
