#include <stdio.h>
#include <stdlib.h>
#if defined(__FreeBSD__)
#include <time.h>
#endif

#include "./include/fetchme.h"
#include "./include/color.h"

int
uptime_info()
{
#if defined(__linux__) && !defined(__FreeBSD__)
	char uptime[100];
	int min = 0;
	float uptime_f = 0;

	FILE *up = fopen("/proc/uptime", "r");
	if (up == NULL) {
		perror("/proc/uptime");
		exit(EXIT_FAILURE);
	}
	fscanf(up, "%99s %*99s", uptime);
	fclose(up);

	sscanf(uptime, "%f", &uptime_f);

	min = ((int)(uptime_f) / 60) % 60;
	printf("%sUptime:\033[0m %d hours, %d mins\n", color_distro(),
		   (int)(uptime_f / 3600), min);
#endif
#if defined(__FreeBSD__) && !defined(__linux__)
	struct timespec time_spec;
	if (clock_gettime(CLOCK_UPTIME_PRECISE, &time_spec) != 0)
		return EXIT_SUCCESS;

	unsigned long uptime = time_spec.tv_sec;
	printf("%sUptime:\033[0m %d hours, %d mins\n", color_distro(),
		   uptime / 3600, (uptime / 60) % 60);
#endif
	return EXIT_SUCCESS;
}
