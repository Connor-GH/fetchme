#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
uptime_info()
{
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

	min = (((float)uptime_f / 3600 - ((int)uptime_f / 3600)) * 60);

	printf("%sUptime:\033[0m %d hours, %d mins\n", color_distro(),
		   (int)(uptime_f / 3600), min);
	return EXIT_SUCCESS;
}
