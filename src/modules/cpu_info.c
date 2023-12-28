#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./include/fetchme.h"

#if LINUX_SUPPORT_ONLY
#include <string.h>
#elif BSD_SUPPORT_ONLY
#include <sys/sysctl.h>
#endif /* string.h or sysctl.h */

size_t
find(char *str, const char *lookfor)
{
	size_t j = 0;
	for (size_t i = 0; i < strlen(str); i++) {
		if (str[i] == lookfor[j]) {
			j++;
			if (j == strlen(lookfor)) {
				return i - j + 1;
			}
		}
	}
	return -1;
}

static char *
remove_first_occurance_from_string(char *str, const char *word)
{
	if (find(str, word) == -1UL) {
		return str;
	} else {
		char *newstr = malloc(strlen(str) - strlen(word) + 1);
		size_t j = 0;
		for (size_t i = 0; i < strlen(str); i++) {
			if ((find(str, word) <= i) &&
				(i < find(str, word) + strlen(word))) {
				continue;
			} else {
				newstr[j] = str[i];
				j++;
			}
		}
		newstr[j] = '\0';
		free(str);
		return newstr;
	}
}
int
cpu_info(const char *color_distro)
{
#if LINUX_SUPPORT_ONLY
	// this long line is used to skip lines.
#define ITER(x)                 \
	for (int i = 0; i < x; i++) \
		while ((c = fgetc(cpu)) != '\n' && c != EOF)

	char model_name[128];
	char *model_name_string = malloc(128);
	int file = 0;

#ifdef CPU_FREQUENCY
	char freq[16]; // cpu frequency
#endif /* CPU_FREQUENCY */
#ifdef CPU_THREADS
	char threads[16]; // cpu threads
#endif /* CPU_THREADS */
#ifdef CPU_TEMP
	double TEMP = 0.0;
	FILE *cpu3 = fopen("/sys/class/hwmon/hwmon1/temp1_input", "r");
#endif /* CPU_TEMP */

	int c;

	FILE *cpu = fopen("/proc/cpuinfo", "r");
	if (cpu == NULL) {
		perror("/proc/cpuinfo");
		exit(EXIT_FAILURE);
	}
	fscanf(cpu, "%127[^\t]\t:", model_name);

	while ((file != EOF) && (strncmp(model_name, "model name", 10) != 0)) {
		ITER(1);
		file = fscanf(cpu, "%127[^\t]\t:", model_name);
	}

	if (file == EOF)
		exit(EXIT_FAILURE);
	fscanf(cpu, "%127[^\n]", model_name_string);

	/* we are on the model name line, get all relevant info */

#if defined(CPU_FREQUENCY) || defined(CPU_THREADS) || defined(CPU_TEMP)
	ITER(3);
#ifdef CPU_FREQUENCY
	fscanf(cpu, "%*15s %*15s \t: %15s", freq);
#endif /* CPU_FREQUENCY */
	ITER(3);
#ifdef CPU_THREADS
	fscanf(cpu, "%*15s \t: %15s", threads);
#endif /* CPU_THREADS */
#endif /* CPU_FREQUENCY || CPU_THREADS || CPU_TEMP */
	fclose(cpu);
#ifdef CPU_TEMP

	if (cpu3 == NULL) {
		cpu3 = fopen("/sys/class/hwmon/hwmon1/temp2_input", "r");
		if (cpu3 == NULL) { /* cpu3 is still NULL after entering temp2_input */
			cpu3 = fopen("/sys/class/hwmon/hwmon1/temp3_input", "r");
			/* Ryzen CPU temperature file not found */
		}
	} else {
		int x2 = 0;
		fscanf(cpu3, "%d", &x2);
		fclose(cpu3);
		TEMP = (x2 / 1000.);
	}
#endif /* CPU_TEMP */
	/* filter out some words */
	char *filter_word_list[] = { "CPU", " with Radeon Graphics", "AMD ",
								 "Intel ", " Processor" };
#define STATIC_ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])
	for (size_t i = 0; i < STATIC_ARRAY_SIZE(filter_word_list); i++) {
		model_name_string = remove_first_occurance_from_string(
			model_name_string, filter_word_list[i]);
	}
	printf("%sCPU:\033[0m%s", color_distro, model_name_string);
	free(model_name_string);

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
#elif BSD_SUPPORT_ONLY /* linux */
	int mib[2];
	char *cpu_name;
	size_t len;
	mib[0] = CTL_HW;
	mib[1] = HW_MODEL;
	sysctl(mib, 2, NULL, &len, NULL, 0);
	cpu_name = malloc(len);
	if (sysctl(mib, 2, cpu_name, &len, NULL, 0) != 0) {
		perror("sysctl");
		exit(EXIT_FAILURE);
	}
	printf("%sCPU: \033[0m%s\n", color_distro, cpu_name);
	free(cpu_name);
#endif /* FreeBSD */
	return EXIT_SUCCESS;
}
