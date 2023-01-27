#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"

#if BSD_SUPPORT_ONLY
#include <time.h>
#endif
int
uptime_info(const char *color_distro)
{
#if LINUX_SUPPORT_ONLY
	char uptime[64];
	int min = 0;
	double uptime_f = 0;

	FILE *up = fopen("/proc/uptime", "r");
	if (up == NULL) {
		perror("/proc/uptime");
		exit(EXIT_FAILURE);
	}
	fscanf(up, "%63s %*63s", uptime);
	fclose(up);

	uptime_f = atof(uptime);

	min = ((int)(uptime_f) / 60) % 60;
	printf("%sUptime:\033[0m %d hours, %d mins\n", color_distro,
		   (int)(uptime_f / 3600), min);
#elif BSD_SUPPORT_ONLY
	struct timespec time_spec;
	if (clock_gettime(CLOCK_UPTIME_PRECISE, &time_spec) != 0)
		return EXIT_SUCCESS;

	unsigned long uptime = time_spec.tv_sec;
	printf("%sUptime:\033[0m %d hours, %d mins\n", color_distro,
		   (int)(uptime / 3600), (int)(uptime / 60) % 60);
#endif
	return EXIT_SUCCESS;
}
