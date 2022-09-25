#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/utsname.h>
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
        // if /etc/conf.d/hostname is NULL, just use utsname
	        struct utsname buffer;
	        if (uname(&buffer) < 0) {
		        perror("uname");
		        exit(EXIT_FAILURE);
            }
            strncpy(hostname_value, buffer.nodename, sizeof (hostname_value)-1);
            // to prevent an fclose()
	        flag = '2';

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
    if (flag != '2') {
    fclose(host); // close /etc/hostname or /etc/conf.d/hostname
    }

    if ((pwd = getpwuid(uid = geteuid())) == NULL) {
        perror("getpwuid() error");
        exit(EXIT_FAILURE);
    }

    /* if this is false, we know that
     * username is a sane size */
    if (strlen(pwd->pw_name) >= 100) {
        fprintf(stderr, "Username is %ld bytes, expected less than "
                "or equal to 100 bytes.\n", strlen(pwd->pw_name));
        exit(EXIT_FAILURE);
    } else {
        const char *const color = color_distro();
        printf("%s%s\033[0m@", color, pwd->pw_name);
        printf("%s%s\033[0m\n", color, hostname_value);


        for (unsigned long i= 0; i < \
                (strlen(pwd->pw_name) + strlen(hostname_value)+1); i++)
            line[i] = '~';
        line[(strlen(pwd->pw_name) + strlen(hostname_value)+1)] = '\0';


        printf("%s%s\033[0m\n", color, line);
    }
    return EXIT_SUCCESS;

}
