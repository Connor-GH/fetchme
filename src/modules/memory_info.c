#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
memory_info(void)
{
#if LINUX_SUPPORT_ONLY
	/*
     * TODO: add sysctl CTL_VM VM_TOTAL for FreeBSD support
     * possibly look into vm.kmem_map_* ?
     */
#define VALUE(x) (fscanf(fp, "%*99s %99s %*99s\n", x))
#define ITER(x)                 \
	for (int i = 0; i < x; i++) \
		while ((c = fgetc(fp)) != '\n' && c != EOF)
	char total[100], freemem[100], buffers[100], cache[100], reclaimable[100];

	double USED_RAM = 0.0;
	int TOTAL_RAM = 0;
	char MorG = 0;
	int t = 0, f = 0, b = 0, ca = 0, r = 0, c;

	FILE *fp = fopen("/proc/meminfo", "r");
	if (fp == NULL) {
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

	sscanf(total, "%d", &t); // total

	sscanf(freemem, "%d", &f); // free

	sscanf(buffers, "%d", &b); // buffers

	sscanf(cache, "%d", &ca); // cache

	sscanf(reclaimable, "%d", &r); //reclaimable

	USED_RAM = ((t - f - b - ca - r) / 1000. / 1000.);

	TOTAL_RAM = (t / 1000 / 1000);

	if (USED_RAM < 1) {
		MorG = 'M';
		USED_RAM *= 1000.;
	} else {
		MorG = 'G';
	}
	printf("%s", color_distro());
	printf("Memory:\033[0m %.1f%c/%dG", USED_RAM, MorG, TOTAL_RAM);
#ifdef MEMORY_PERCENT
	printf(" (%.0f%%)", ((double)(t - f - b - ca - r) / (double)t) * 100);
#endif
	printf("\n");

#endif
	return EXIT_SUCCESS;
}
