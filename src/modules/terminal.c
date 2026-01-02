#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/fetchme.h"

int
terminal(const char *color_distro)
{
#if UNIX_SUPPORT
	extern char **environ;
	char *terminal_emulator = getenv("TERM");

	if (terminal_emulator == NULL) {
		perror("getenv TERM");
		exit(EXIT_FAILURE);
	}
	printf("%sTerminal:\033[0m %s\n", color_distro, terminal_emulator);
#endif
	return EXIT_SUCCESS;
}
