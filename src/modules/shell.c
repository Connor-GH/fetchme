#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "./include/fetchme.h"
int
shell(const char *color_distro)
{
#if UNIX_SUPPORT
	char *shell = getenv("SHELL");

	if (shell == NULL) {
		perror("getenv SHELL");
		exit(EXIT_FAILURE);
	}
	printf("%sShell:\033[0m %s\n", color_distro, basename(shell));
#endif
	return EXIT_SUCCESS;
}
