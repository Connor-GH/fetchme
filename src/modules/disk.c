#include <stdio.h>
#include <sys/statvfs.h>
#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

int disk() {
    const char *filename = "/";

    struct statvfs buf;
    if (!statvfs(filename, &buf)) {

        unsigned long blksize, blocks, freeblks, disk_size, used, free;
        blksize = buf.f_bsize;
        blocks = buf.f_blocks;
        freeblks = buf.f_bfree;
        int unit;

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
        printf(COLOR);
        printf("Disk:\033[0m %lu%c/%lu%c", \
                (used/1024/1024/1024), \
                unit, ((used/1024/1024/1024)+free/1024/1024/1024), unit);
#ifdef DISK_PERCENT
        printf(" (%.0f%%)", \
              (((float)(used/1024/1024/1024.)/(float)((used/1024/1024/1024)+free/1024/1024/1024.)) * 100));
#endif
        printf("\n");
        }
        else {
            printf("Couldn't get file system statistics\n");
        }
    return 0;
}
