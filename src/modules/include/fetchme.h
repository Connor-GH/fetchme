#ifndef FETCHME_H
#define FETCHME_H

#if (defined(__linux__))
#define LINUX_SUPPORT 1
#else
#define LINUX_SUPPORT 0
#endif

#if (defined(__FreeBSD__) || defined(__OpenBSD__))
#define BSD_SUPPORT 1
#else
#define BSD_SUPPORT 0
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define APPLE_SUPPORT 1
#else
#define APPLE_SUPPORT 0
#endif

#if (LINUX_SUPPORT && !(APPLE_SUPPORT && BSD_SUPPORT))
#define LINUX_SUPPORT_ONLY 1
#else
#define LINUX_SUPPORT_ONLY 0
#endif

#if (BSD_SUPPORT && !(LINUX_SUPPORT && APPLE_SUPPORT))
#define BSD_SUPPORT_ONLY 1
#else
#define BSD_SUPPORT_ONLY 0
#endif

#if (APPLE_SUPPORT && !(LINUX_SUPPORT && BSD_SUPPORT))
#define APPLE_SUPPORT_ONLY 1
#else
#define APPLE_SUPPORT_ONLY 0
#endif

#if (defined(__unix__) || defined(__unix) || defined(unix))
#define UNIX_DEFINED_MACRO_SUPPORT 1
#else
#define UNIX_DEFINED_MACRO_SUPPORT 0
#endif

#if (LINUX_SUPPORT || BSD_SUPPORT || APPLE_SUPPORT || \
	 UNIX_DEFINED_MACRO_SUPPORT)
#define UNIX_SUPPORT 1
#else
#define UNIX_SUPPORT 0
#endif

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
#if GPU_INFO == 2
int
gpu_info_v2(void);
#else
int
gpu_info_v1(void);
#endif
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
