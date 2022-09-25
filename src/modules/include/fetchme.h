#ifndef FETCHME_H
#define FETCHME_H
#ifdef CPU
int
cpu_info(void);
#endif
#ifdef DISK
int
disk(void);
#endif
#ifdef DISTRO
int
distro(void);
#endif
#ifdef GPU
int
gpu_info(void);
#endif
#ifdef KERNEL
int
kernel(void);
#endif
#ifdef MEMORY
int
memory_info(void);
#endif
#ifdef PACKAGE
int
package_count(void);
#endif
#ifdef REFRESH_RATE
int
refresh_rate(void);
#endif
#ifdef RESOLUTION
int
resolution(void);
#endif
#ifdef SHELL
int
shell(void);
#endif
#ifdef TERMINAL
int
terminal(void);
#endif
#ifdef UPTIME
int
uptime_info(void);
#endif
#ifdef USERNAME_HOSTNAME
int
username_at_hostname(void);
#endif
#ifdef WM
int
wm(void);
#endif
#endif /* FETCHME_H */
