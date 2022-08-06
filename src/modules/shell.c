#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "./include/fetchme.h"
#include "./include/color.h"
int shell() {
    struct passwd *p;
    uid_t uid;

    if ((p = getpwuid(uid = geteuid())) == NULL)
        perror("getpwuid() error");
    else {
        printf("%s", color_distro());
        printf("Shell:\033[0m %s\n", p->pw_shell);
        return 0;
    }
return -1;
}
