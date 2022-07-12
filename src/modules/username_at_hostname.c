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
        FILE *host = fopen("/etc/hostname", "r");
        if(host == NULL) {
                printf("No hostname found, exiting...\n");
                exit(EXIT_FAILURE);
        }
        fscanf(host, "%99s", hostname_value);

        fclose(host);
        struct passwd *pwd;

        if ((pwd = getpwuid(uid = geteuid())) == NULL) {
            perror("getpwuid() error");
            exit(EXIT_FAILURE);
        }
        else {
            printf(COLOR);
            printf("%s\033[0m@", pwd->pw_name);
            printf(COLOR);
            printf("%s\033[0m\n", hostname_value);

            int hostname_len = \
            (strlen(pwd->pw_name) + strlen(hostname_value));

            char line[hostname_len+1]; /* Accounts for user 'foo',
                                        * hostname 'bar', and the '+1'
                                        * accounts for the @ symbol.
                                        *
                                        * Variable length arrays are
                                        * forbidden in ISO C90 so this
                                        * should be changed to avoid a warning. */

            for (int i= 0; i < hostname_len+1; i++) line[i] = '~';
            line[hostname_len+1] = '\0';

            printf(COLOR);
            printf("%s\033[0m\n", line);
    }
    return EXIT_SUCCESS;

}
