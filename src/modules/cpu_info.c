#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
cpu_info()
{
#define ITER(x) (for (int i = 0; i < x; i++) \
        while ((c = fgetc(cpu)) != '\n' && c != EOF))

    char brand[10];     // cpu brand
    char lineup[10];    // lineup (Ryzen, Core, Xeon, Epyc, etc)
    char sublineup[10]; // sublineup (5, 7, 9 or i5 i7 i9 etc)
    char model_num[10]; // model number (3600, 9900k, 3900X, etc)
#ifdef CPU_FREQUENCY
    char freq[10];  // cpu frequency
#endif /* CPU_FREQUENCY */
#ifdef CPU_THREADS
    char threads[10];   // cpu threads
#endif /* CPU_THREADS */
#ifdef CPU_TEMP
    float TEMP;
    FILE *cpu3 = fopen("/sys/class/hwmon/hwmon1/temp3_input", "r");
#endif /* CPU_TEMP */

    int c;

    FILE *cpu = fopen("/proc/cpuinfo", "r");
    if (cpu == NULL) {
        perror("/proc/cpuinfo");
        exit(EXIT_FAILURE);
        }
    // this long line is used to skip lines.
    //for (int i = 0; i < 4; i++)
        //while ((c = fgetc(cpu)) != '\n' && c != EOF);
    ITER(4);

    fscanf(cpu, "%*9s %*9s \t: %9s %9s %9s %9s", \
            brand, lineup, sublineup, model_num);
#if defined(CPU_FREQUENCY) || defined(CPU_THREADS) || defined(CPU_TEMP)
    /*for (int i = 0; i < 3; i++)
        while ((c = fgetc(cpu)) != '\n' && c != EOF);*/
    ITER(3);

#ifdef CPU_FREQUENCY
    fscanf(cpu, "%*9s %*9s \t: %9s", freq);
#endif /* CPU_FREQUENCY */
    /*for (int i = 0; i < 3; i++)
        while ((c = fgetc(cpu)) != '\n' && c != EOF);*/
    ITER(3);

#ifdef CPU_THREADS
    fscanf(cpu, "%*9s \t: %9s", threads);
#endif /* CPU_THREADS */
#endif /* CPU_FREQUENCY || CPU_THREADS || CPU_TEMP */
    fclose(cpu);
#ifdef CPU_TEMP

    if (cpu3 == NULL) {
        TEMP = 0.;
    } else {
        char line1_value[100];
        int x2 = 0;
        fscanf(cpu3, "%99s", line1_value);
        fclose(cpu3);
        sscanf(line1_value, "%d", &x2);
        TEMP = (x2/1000.);
    }
#endif /* CPU_TEMP */

    printf("%sCPU:\033[0m %s %s %s %s",\
        color_distro(), brand, lineup, sublineup, model_num);


#ifdef CPU_THREADS
    printf(" (%s)", threads);
#endif /* CPU_THREADS */
#ifdef CPU_FREQUENCY
    printf(" @ %sMHz", freq);
#endif /* CPU_FREQUENCY */
#ifdef CPU_TEMP
  printf(" (%.1f°C)", TEMP);
#endif /* CPU_TEMP */
printf("\n");
    return EXIT_SUCCESS;
}
