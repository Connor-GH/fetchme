#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"

int
memory_info(const char *color_distro)
{
#if LINUX_SUPPORT_ONLY
	/*
     * TODO: add sysctl CTL_VM VM_TOTAL for FreeBSD support
     * possibly look into vm.kmem_map_* ?
     */
#define VALUE(x) (fscanf(fp, "%*63s %63s %*63s\n", x))
#define ITER(x)                 \
	for (int i = 0; i < x; i++) \
		while ((c = fgetc(fp)) != '\n' && c != EOF)
	char total[64], freemem[64], buffers[64], cache[64], reclaimable[64];

	double USED_RAM = 0.0;
	double TOTAL_RAM = 0.0;
    const char *used_MorG;
    const char *total_MorG;
	int t = 0, f = 0, b = 0, ca = 0, r = 0, c;

	FILE *fp = fopen("/proc/meminfo", "r");
	if (unlikely(fp == NULL)) {
		perror("/proc/meminfo");
		exit(EXIT_FAILURE);
	}
	// this is a mess to look at but I don't see another alternative

	VALUE(total);
	VALUE(freemem);

	while ((c = fgetc(fp)) != '\n' && c != EOF)
		;

	VALUE(buffers);
	VALUE(cache);

	ITER(18);

	VALUE(reclaimable);

	fclose(fp);

	t = atoi(total);
	f = atoi(freemem);
	b = atoi(buffers);
	ca = atoi(cache);
	r = atoi(reclaimable);

	USED_RAM = ((t - f - b - ca - r) / 1048576.);

	TOTAL_RAM = (t / 1048576.);

    /* Not many modern machines have less than 1GiB memory */
    if (unlikely(TOTAL_RAM < 1)) {
		used_MorG = "MiB";
		USED_RAM *= 1024.;
		total_MorG = "MiB";
		TOTAL_RAM *= 1024.;
    } else {
		total_MorG = "GiB";
        if (USED_RAM < 1) {
		    USED_RAM *= 1024.;
		    used_MorG = "MiB";
        } else {
		    used_MorG = "GiB";
        }
    }

    // Round memory to nearest whole number. This also fixes a bug
    // where laptops would show 3G of memory instead of 3.8G or so
    // due to the integrated graphics using system memory as VRAM.
	printf("%sMemory:\033[0m %.1f%s/%d%s", color_distro, USED_RAM, used_MorG,
		   (int)(TOTAL_RAM+0.5), total_MorG);
#ifdef MEMORY_PERCENT
	printf(" (%.0f%%)", ((double)(t - f - b - ca - r) / (double)t) * 100.);
#endif
	printf("\n");

#endif
	return EXIT_SUCCESS;
}
