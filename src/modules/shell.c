#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"
int
shell()
{
    struct passwd *p;
    uid_t uid;

    if ((p = getpwuid(uid = geteuid())) == NULL) {
        perror("getpwuid() error");
        return 1;
    }
        printf("%sShell:\033[0m %s\n", \
                color_distro(), p->pw_shell);
        return 0;
}
