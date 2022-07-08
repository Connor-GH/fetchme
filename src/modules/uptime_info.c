#include <stdio.h>
#include <stdlib.h>

#include "./include/uptime_info.h"
#include "./include/color.h"
#include "./include/config.h"

int uptime_info() {
    char uptime[100];
    FILE *up = fopen("/proc/uptime", "r");
        if (up == NULL) {
            printf("No uptime found, exiting");
            return -1;
        }
    fscanf(up, "%99s %*99s", uptime);
    fclose(up);

    float uptime_f;
    sscanf(uptime, "%f", &uptime_f);

    int min = (((float)uptime_f / 3600) - ((int)(uptime_f / 3600))) * 60;
    printf(COLOR);
    printf("Uptime:\033[0m %d hours, %d mins\n", \
            (int)(uptime_f / 3600), min);
    return 0;

}
