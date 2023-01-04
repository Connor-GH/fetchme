#include <stdio.h>
#include <stdlib.h>

#include <sys/utsname.h>

#include "./include/fetchme.h"

int
kernel(const char *color_distro)
{
#if UNIX_SUPPORT
	struct utsname buffer;
	if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
	}
	printf("%sKernel:\033[0m %s\n", color_distro, buffer.release);

#endif
	return EXIT_SUCCESS;
}
