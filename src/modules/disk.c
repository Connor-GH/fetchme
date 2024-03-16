#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/statvfs.h>
int
disk(const char *color_distro)
{
	/*
     * When multi-drive filesystem
     * usage is finished, this will be a
     * `const char' instead of a `const char const'
     * to show that the value pointed to can change
     * (useful in an if-else statement for drives)
     */
	const char *const filename = "/";
	struct statvfs buf;
	if (!statvfs(filename, &buf)) {
		uint64_t frsize, blocks, freeblks, disk_size, used, free;
		char unit;

		frsize = (uint64_t)buf.f_frsize;
		blocks = buf.f_blocks;
		freeblks = buf.f_bfree;

		disk_size = blocks * frsize;
		free = freeblks * frsize;
		used = disk_size - free;

		if ((used > 1024ULL * 1024 * 1024) &&
			(used < 1024ULL * 1024 * 1024 * 1024)) {
			unit = 'G';
		} else if ((used > 1024ULL * 1024) && (used < 1024ULL * 1024 * 1024)) {
			unit = 'M';
		} else {
			unit = 'T';
		}
		printf("%sDisk:\033[0m %llu%c/%llu%c", color_distro,
			   (used / 1024ULL / 1024 / 1024), unit,
			   ((used / 1024ULL / 1024 / 1024) + free / 1024ULL / 1024 / 1024),
			   unit);
#ifdef DISK_PERCENT
		printf(" (%.0f%%)", (((double)(used / 1024ULL / 1024 / 1024.) /
							  (double)((used / 1024ULL / 1024 / 1024.) +
									   free / 1024UL / 1024 / 1024.)) *
							 100));
#endif /* DISK_PERCENT */
		printf("\n");
	} else {
		fprintf(stderr, "Couldn't get file system statistics\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
