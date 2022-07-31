#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/config.h"
#include "./include/color.h"
int cpu_info() {

    char brand[10];     // cpu brand
    char lineup[10];    // lineup (Ryzen, Core, Xeon, Epyc, etc)
    char sublineup[10]; // sublineup (5, 7, 9 or i5 i7 i9 etc)
    char model_num[10]; // model number (3600, 9900k, 3900X, etc)
    char freq[10];      //cpu frequency
    char threads[10];   //cpu threads
#ifdef CPU_TEMP
    float TEMP;
#endif

    int c;

    FILE *cpu = fopen("/proc/cpuinfo", "r");
    if (cpu == NULL) {
        printf("cpuinfo not found\n");
        exit(EXIT_FAILURE);
        }
    // this long line is used to skip lines.
    for (int i = 0; i < 4; i++) while ((c = fgetc(cpu)) != '\n' && c != EOF);

    fscanf(cpu, "%*9s %*9s \t: %9s %9s %9s %9s", \
            brand, lineup, sublineup, model_num);
    for(int i = 0; i < 3; i++) while ((c = fgetc(cpu)) != '\n' && c != EOF);


    fscanf(cpu, "%*9s %*9s \t: %9s", freq);
    for(int i = 0; i < 3; i++) while ((c = fgetc(cpu)) != '\n' && c != EOF);
    

    fscanf(cpu, "%*9s \t: %9s", threads);
    fclose(cpu);
#ifdef CPU_TEMP
    FILE *cpu3 = fopen("/sys/class/hwmon/hwmon1/temp3_input", "r");

    if (cpu3 == NULL) TEMP = 0.;

    else {
    char line1_value[100];
    fscanf(cpu3, "%99s", line1_value);
    fclose(cpu3);
    int x2;
    sscanf(line1_value, "%d", &x2);
    TEMP =(x2/1000.);
    }
#endif


    printf("%s", color_distro());
    printf("CPU:\033[0m %s %s %s %s",\
        brand, lineup, sublineup, model_num);


#ifdef CPU_THREADS
    printf(" (%s)", threads);
#endif
#ifdef CPU_FREQUENCY
    printf(" @ %sMHz", freq);
#endif
#ifdef CPU_TEMP
  printf(" (%.1f°C)", TEMP);
#endif
printf("\n");
    return EXIT_SUCCESS;
}
