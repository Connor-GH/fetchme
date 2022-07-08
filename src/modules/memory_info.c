#include <stdio.h>
#include <stdlib.h>

#include "./include/memory_info.h"
#include "./include/color.h"
#include "./include/config.h"

int memory_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if(fp == NULL) {
        printf("Unable to return meminfo\n");
        exit(EXIT_FAILURE);
    }
    char total[100];
    char free[100];
    char buffers[100];
    char cache[100];
    char shared[100];
    char reclaimable[100];

    int c = 0;
    // this is a mess to look at but I don't see another alternative

    fscanf(fp, "%*99s %99s", total);
    while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s", free);
    for (int i = 0; i < 2; i++) while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s", buffers);
    while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s", cache);
    for (int i = 0; i < 16; i++) while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s", shared);
    for (int i = 0; i < 3; i++) while ((c = fgetc(fp)) != '\n' && c != EOF);

    fscanf(fp, "%*99s %99s", reclaimable);


    fclose(fp);


    int t;
    sscanf(total, "%d", &t);      // total

    int f;
    sscanf(free, "%d", &f);       // memfree
                            
    int b;
    sscanf(buffers, "%d", &b);    // buffers
    
    int ca;
    sscanf(cache, "%d", &ca);     // cache
    
    int s;
    sscanf(shared, "%d", &s);     // shmem
    
    int r;
    sscanf(reclaimable, "%d", &r);//reclaimable

    float USED_RAM = (t + s - f - b - ca - r)/1024./1024.;

    int TOTAL_RAM = (t/1000/1000);

    int MorG;                  // use MiB or GiB
    if (USED_RAM < 1) {
        MorG = 'M';
        USED_RAM = (USED_RAM * 1000);
    }
    else {
        MorG = 'G';
    }
    printf(COLOR);
    printf("Memory:\033[0m %.1f%c/%dG\n", \
            USED_RAM, MorG, TOTAL_RAM);

    return EXIT_SUCCESS;
}
