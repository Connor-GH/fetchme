#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"
int
shell()
{
    extern uid_t getuid(void);
    extern uid_t geteuid(void);
	struct passwd *p;
	uid_t uid;
    char shell[20];

	if ((p = getpwuid(uid = geteuid())) == NULL) {
		perror("getpwuid() error");
		exit(EXIT_FAILURE);
	}
    sscanf(p->pw_shell, "/bin/%19s", shell);
	printf("%sShell:\033[0m %s\n", color_distro(), shell);
	return EXIT_SUCCESS;
}
