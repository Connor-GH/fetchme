#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
memory_info()
{
#define VALUE(x) (fscanf(fp, "%*99s %99s %*99s\n", x))
    char total[100];
    char freemem[100];
    char buffers[100];
    char cache[100];
    char shared[100];
    char reclaimable[100];

    float USED_RAM = 0.0;
    int TOTAL_RAM = 0;
    char MorG = 0;
    int t,f,b,ca,s,r,c = 0;

    FILE *fp = fopen("/proc/meminfo", "r");
    if( fp == NULL) {
        perror("/proc/meminfo");
        exit(EXIT_FAILURE);
    }
    // this is a mess to look at but I don't see another alternative

    VALUE(total);
    VALUE(freemem);

    while ((c = fgetc(fp)) != '\n' && c != EOF);

    VALUE(buffers);
    VALUE(cache);

    for (int i = 0; i < 15; i++)
        while ((c = fgetc(fp)) != '\n' && c != EOF);

    VALUE(shared);

    for (int i = 0; i < 2; i++)
        while ((c = fgetc(fp)) != '\n' && c != EOF);

    VALUE(reclaimable);

    fclose(fp);


    sscanf(total, "%d", &t);      // total

    sscanf(freemem, "%d", &f);    // free

    sscanf(buffers, "%d", &b);    // buffers

    sscanf(cache, "%d", &ca);     // cache

    sscanf(shared, "%d", &s);     // shmem

    sscanf(reclaimable, "%d", &r);//reclaimable


    USED_RAM = (float)((t + s - f - b - ca - r)/1000./1000.);

    TOTAL_RAM = (t/1000/1000);

    if (USED_RAM < 1) {
        MorG = 'M';
        USED_RAM = (USED_RAM * 1000);
    }
    else {
        MorG = 'G';
    }
    printf("%s", color_distro());
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
    /*
     * explanation for pragma:
     * we explicitly want to
     * convert to double here.
     * */
    printf("Memory:\033[0m %.1f%c/%dG", \
            USED_RAM, MorG, TOTAL_RAM);
#ifdef MEMORY_PERCENT
    printf(" (%.0f%%)", ((float) \
        (t + s - f - b - ca - r) / (float) t) * 100);
#pragma clang diagnostic pop
#endif
    printf("\n");

    return EXIT_SUCCESS;
}
