#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/fetchme.h"
#include "./include/color.h"
int
shell()
{
	extern char **environ;
	char *shell = NULL;

	for (size_t i = 0; environ[i] != NULL; i++) {
		char *eq = strchr(environ[i], '=');
		if (eq == NULL)
			exit(EXIT_FAILURE);

		*eq = '\0';

		if (strncmp(environ[i], "SHELL", 5) == 0)
			shell = eq + 1;

		*eq = '=';
	}
	if (shell == NULL) {
		perror("SHELL (env var)");
		exit(EXIT_FAILURE);
	}
	sscanf(shell, "/bin/%s", shell);
	printf("%sShell:\033[0m %s\n", color_distro(), shell);
	return EXIT_SUCCESS;
}
