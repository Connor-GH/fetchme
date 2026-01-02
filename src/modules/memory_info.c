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

	double used_ram = 0.0;
	double total_ram = 0.0;
	const char *used_ram_unit;
	const char *total_ram_unit;
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

	used_ram = ((t - f - b - ca - r) / 1048576.);

	total_ram = (t / 1048576.);

	/* Not many modern machines have less than 1GiB memory */
	if (unlikely(total_ram < 1)) {
		used_ram_unit = "MiB";
		used_ram *= 1024.;
		total_ram_unit = "MiB";
		total_ram *= 1024.;
	} else {
		total_ram_unit = "GiB";
		if (used_ram < 1) {
			used_ram *= 1024.;
			used_ram_unit = "MiB";
		} else {
			used_ram_unit = "GiB";
		}
	}

	printf("%sMemory:\033[0m %.1f%s/%.1f%s", color_distro, used_ram,
		   used_ram_unit, total_ram, total_ram_unit);
#ifdef MEMORY_PERCENT
	printf(" (%.0f%%)", ((double)(t - f - b - ca - r) / (double)t) * 100.);
#endif
	printf("\n");

#endif
	return EXIT_SUCCESS;
}
