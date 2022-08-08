#include <stdio.h>
#include <sys/statvfs.h>
#include "./include/fetchme.h"
#include "./include/color.h"

int disk() {
    const char *filename = "/";

    struct statvfs buf;
    if (!statvfs(filename, &buf)) {

        unsigned long blksize, blocks, freeblks, disk_size, used, free;
        char unit = 0;

        blksize = buf.f_bsize;
        blocks = buf.f_blocks;
        freeblks = buf.f_bfree;

        disk_size = blocks * blksize;
        free = freeblks * blksize;
        used = disk_size - free;

        if ((used > 1024L*1024*1024) && (used < 1024L*1024*1024*1024)) {
            unit = 'G';
        }
        else if ((used > 1024L*1024) && (used < 1024L*1024*1024)) {
            unit = 'M';
        }
        else {
            unit = 'T';
        }
        printf("%sDisk:\033[0m %ld%c/%ld%c", \
                color_distro(), (used/1024/1024/1024), \
                unit, ((used/1024/1024/1024)+free/1024/1024/1024), unit);
#ifdef DISK_PERCENT
        printf(" (%.0f%%)", \
              (((float)(used/1024/1024/1024.)/(float)((used/1024/1024/1024)+free/1024/1024/1024.)) * 100));
#endif
        printf("\n");
        }
        else {
            fprintf(stderr, "Couldn't get file system statistics\n");
            return 1;
        }
    return 0;
}
