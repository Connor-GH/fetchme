#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
terminal()
{
	extern char **environ;
	char *terminal_emulator = NULL;

	for (size_t i = 0; environ[i] != NULL; i++) {
		char *eq = strchr(environ[i], '=');

		if (eq == NULL)
			exit(EXIT_FAILURE);

		*eq = '\0';

		if (strcmp(environ[i], "TERM") == 0) {
			terminal_emulator = eq + 1;
            break;
        }

		*eq = '=';
	}
	if (terminal_emulator == NULL) {
		fprintf(stderr, "wrong ENV var directory\n");
		exit(EXIT_FAILURE);
	}
	printf("%sTerminal:\033[0m %s\n", color_distro(), terminal_emulator);
	return EXIT_SUCCESS;
}
