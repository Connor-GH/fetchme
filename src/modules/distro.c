#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>

#include "./include/fetchme.h"

int
distro(const char *color_distro)
{
#if UNIX_SUPPORT
	struct utsname buffer;

	char os_name[64];
	char info_desc[32];

	FILE *os_release = fopen("/etc/os-release", "r");

	if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
	}

	if (os_release == NULL) {
		perror("/etc/os-release");
		exit(EXIT_FAILURE);
	}

	while (fgets(os_name, sizeof(os_name), os_release) != NULL) {
		/*
         * get info of description, as well as
         * remove quotation marks from
         * os name if needed.
         */
		sscanf(os_name, "%31[^=]=\"%63[^\"]", info_desc, os_name);
		/*
         * only check the first 11 bytes for
         * PRETTY_NAME.
         */
		if (strncmp(info_desc, "PRETTY_NAME", 11) == 0) {
			fclose(os_release);
			printf("%sOS:\033[0m %s %s\n", color_distro, os_name,
				   buffer.machine);
			return EXIT_SUCCESS;
		}
	}
	fclose(os_release);
	fprintf(stderr, "Distro name not found.\n");

	exit(EXIT_FAILURE);
#else
	return EXIT_SUCCESS;
#endif
}
