#include "./include/fetchme.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
uptime_info(const char *color_distro)
{
	int min = 0;
	int hours = 0;
	int days = 0;
	struct timespec time_spec;
	if (clock_gettime(CLOCK_BOOTTIME, &time_spec) != 0)
		return EXIT_SUCCESS;

	time_t uptime = time_spec.tv_sec;

	min = ((int)uptime / 60) % 60;
	hours = (int)(uptime / 3600);
	days = hours / 24;
	hours %= 60;
	printf("%sUptime:\033[0m ", color_distro);
	if (days > 0)
		printf("%d days, ", days);
	printf("%d hours, %d mins\n", hours, min);

	return EXIT_SUCCESS;
}
