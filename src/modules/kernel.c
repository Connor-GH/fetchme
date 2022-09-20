#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/utsname.h>
#include "./include/fetchme.h"
#include "./include/color.h"

int
kernel()
{
    struct utsname buffer;
    errno = 0;
    if (uname(&buffer) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
        }
    printf("%sKernel:\033[0m %s\n", \
            color_distro(), buffer.release);


    return EXIT_SUCCESS;

}
