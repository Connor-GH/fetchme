#include <stdio.h> // for those two printfs
#include "./modules/include/color.h"
#include "./modules/include/fetchme.h"
/* 
 * the current state:
 *
 * - 1:1 features with the previous 
 *   version (repo private)
 *
 * - bug patching needed (as always)
 * - code style rework
 */

int main(void) {
    // disable line wrapping.
    // yes, I disabled 
    // line wrapping for
    // something this simple.

    printf("\033[?7l");
#ifdef USERNAME_HOSTNAME 
    username_at_hostname(); 
#endif

#ifdef DISTRO
    distro();
#endif

#ifdef KERNEL
    kernel();
#endif

#ifdef UPTIME
    uptime_info();
#endif

#ifdef PACKAGE
    package_count();
#endif

#ifdef SHELL
    shell();
#endif

#ifdef RESOLUTION
    resolution();
#endif

#ifdef REFRESH_RATE
    refresh_rate();
#endif

#ifdef WM
    wm();
#endif

#ifdef TERMINAL
    terminal();
#endif

#ifdef CPU
    cpu_info();
#endif

#ifdef GPU
    gpu_info();
#endif

#ifdef MEMORY
    memory_info();
#endif

#ifdef DISK
    disk();
#endif
    // enable line wrapping
    printf("\033[?7h");

return 0;
}
