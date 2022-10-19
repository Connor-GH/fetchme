#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>
#include <sys/types.h>

#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
username_at_hostname()
{
	extern uid_t getuid(void);
	extern uid_t geteuid(void);
	char hostname_value[100];
	uid_t uid;
	struct passwd *pwd;
	char line[200]; /* Accounts for user 'foo',
                     * hostname 'bar', and the '+1'
                     * accounts for the @ symbol.
                     *
                     * This is fine as long as
                     * the username is not 101
                     * bytes long. (this "fixes" a VLA) */

	struct utsname buffer;
	if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
	}
	strncpy(hostname_value, buffer.nodename, sizeof(hostname_value) - 1);

	if ((pwd = getpwuid(uid = geteuid())) == NULL) {
		perror("getpwuid() error");
		exit(EXIT_FAILURE);
	}

	/* if this is true, we know that
     * username is a sane size */
	if (strlen(pwd->pw_name) < 100) {
		const char *const color = color_distro();
		printf("%s%s\033[0m@%s%s\033[0m\n", color, pwd->pw_name, color,
			   hostname_value);

		for (unsigned long i = 0;
			 i < (strlen(pwd->pw_name) + strlen(hostname_value) + 1); i++)
			line[i] = '~';

		line[(strlen(pwd->pw_name) + strlen(hostname_value) + 1)] = '\0';

		printf("%s%s\033[0m\n", color, line);
	} else {
		fprintf(stderr,
				"Username is %ld bytes, expected less than "
				"or equal to 100 bytes.\n",
				strlen(pwd->pw_name));
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
