#include "./modules/include/username_at_hostname.h"
#include "./modules/include/distro.h"
#include "./modules/include/kernel.h"
#include "./modules/include/uptime_info.h"
#include "./modules/include/package_count.h"
#include "./modules/include/shell.h"
#include "./modules/include/resolution.h"
#include "./modules/include/refresh_rate.h"
#include "./modules/include/wm.h"
#include "./modules/include/terminal.h"
#include "./modules/include/cpu_info.h"
#include "./modules/include/gpu_info.h"
#include "./modules/include/memory_info.h"
#include "./modules/include/disk.h"

#include "./modules/include/config.h"
/* 
 * the current state:
 *
 * - 1:1 features with the previous 
 *   version (repo private)
 *
 * - bug patching needed (as always)
 * - code style rework
 */

int main(int argc, char** argv, char** envp) {
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
    terminal(envp);
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

return 0;
}
