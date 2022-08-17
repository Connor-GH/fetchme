#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
username_at_hostname()
{
    char hostname_value[100];
    uid_t  uid;
    struct passwd *pwd;
    char flag = '0';
    char line[200];            /* Accounts for user 'foo',
                                * hostname 'bar', and the '+1'
                                * accounts for the @ symbol.
                                *
                                * This is fine as long as 
                                * the username is not 101
                                * bytes long. (this "fixes" a VLA) */

    FILE *host = fopen("/etc/hostname", "r");
    if (host == NULL) {
        flag = '1'; // set a flag that parsing is needed
        host = fopen("/etc/conf.d/hostname", "r");

        if (host == NULL) {
            // if /etc/conf.d/hostname is NULL, end the program
            perror("/etc/hostname and /etc/conf.d/hostname");
            exit(EXIT_FAILURE);
        }
    }
    if (flag == '0') { // using a flag prevents a double free
        fscanf(host, "%99s", hostname_value);
    }

    if (flag == '1') {
        char temp[110];
        int c;
        fscanf(host, "%109s", temp);

        // if the line is blank, skip a line
        while (strstr(temp, "hostname=") == NULL) { 
            while ((c = fgetc(host)) != '\n' && c != EOF); 
            fscanf(host, "%109s", temp); // grab that line
        }
        sscanf(temp, "hostname=\"%[^\"\n]", hostname_value); // parse string
    }
    fclose(host); // close /etc/hostname or /etc/conf.d/hostname

    if ((pwd = getpwuid(uid = geteuid())) == NULL) {
        perror("getpwuid() error");
        exit(EXIT_FAILURE);
    }

    /* if this is false, we know that
     * username is a sane size */
    if (strlen(pwd->pw_name) >= 100) { 
        fprintf(stderr, "Username too long.\n");
        fprintf(stderr, "Username is %ld bytes, expected less than "
                "or equal to 100 bytes.\n", strlen(pwd->pw_name));
        exit(EXIT_FAILURE);
    }
    else {
        const char *color = color_distro();
        printf("%s%s\033[0m@", color, pwd->pw_name);
        printf("%s%s\033[0m\n", color, hostname_value);


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
     * and thus returns one. this is no issue here. This may be 
     * a warning because it's a portability issue, however.
     */
        for (int i= 0; i < \
                (strlen(pwd->pw_name) + strlen(hostname_value)+1); i++) 
            line[i] = '~';
#pragma clang diagnostic pop
        line[(strlen(pwd->pw_name) + strlen(hostname_value)+1)] = '\0';


        printf("%s%s\033[0m\n", color, line);
    }
    return EXIT_SUCCESS;

}
