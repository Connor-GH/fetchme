#ifndef FETCHME_H
#define FETCHME_H

#if __GNUC__ > 2 || __GNUC_MINOR__ >= 96 || __has_builtin(__builtin_expect)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif

#if (defined(__linux__))
#define LINUX_SUPPORT 1
#else
#define LINUX_SUPPORT 0
#endif

#if (defined(__gnu_hurd__)
#define HURD_SUPPORT 1
#else
#define HURD_SUPPORT 0
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
cpu_info(const char *color_distro);
#endif
#ifdef DISK
int
disk(const char *color_distro);
#endif
#ifdef DISTRO
int
distro(const char *color_distro);
#endif
#ifdef GPU
int
gpu_info(const char *color_distro);
#if GPU_INFO == 2
int
gpu_info_v2(const char *color_distro);
#else
int
gpu_info_v1(const char *color_distro);
#endif
#endif
#ifdef KERNEL
int
kernel(const char *color_distro);
#endif
#ifdef MEMORY
int
memory_info(const char *color_distro);
#endif
#ifdef PACKAGE
int
package_count(const char *color_distro);
#endif
#ifdef REFRESH_RATE
int
refresh_rate(const char *color_distro);
#endif
#ifdef RESOLUTION
int
resolution(const char *color_distro);
#endif
#ifdef SHELL
int
shell(const char *color_distro);
#endif
#ifdef TERMINAL
int
terminal(const char *color_distro);
#endif
#ifdef UPTIME
int
uptime_info(const char *color_distro);
#endif
#ifdef USERNAME_HOSTNAME
int
username_at_hostname(const char *color_distro);
#endif
#ifdef WM
int
wm(const char *color_distro);
#endif
#endif /* FETCHME_H */
