#include "color.h"
/*
 * extremely cheap and easy 
 * config using macros
 * (this is awful)
 *
 * Basically, comment out
 * whatever info section you 
 * don't want. The only exception
 * is that you need RESOLUTION
 * if you use REFRESH_RATE, but
 * not the other way around.
 */

/* 
 * USERNAME_HOSTNAME
 * also controls the 
 * line seperator
 * under it.
 */
// define this if you don't want an automatically-chosen distro color.
/* #define CUSTOM_COLOR */

// use this to define a custom color. available colors are in color.h
/* #define CUSTOM_COLOR_VALUE CYAN */

#define USERNAME_HOSTNAME
#define DISTRO
#define KERNEL
#define UPTIME
//#define PACKAGE uncommented for compatability
#define SHELL
#define RESOLUTION
/*
 * REFRESH_RATE is the slowest module and
 * that's actually why it has its own module 
 * instead of being with resolution.
 */
//#define REFRESH_RATE
#define WM
#define TERMINAL
#define CPU
#define CPU_THREADS
//#define CPU_TEMP // VERY EXPERIMENTAL! 
//#define CPU_FREQUENCY
#define GPU
#define MEMORY
#define MEMORY_PERCENT
#define DISK
//#define DISK_PERCENT
