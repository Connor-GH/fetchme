#include <stdio.h> // for those three printfs and one fprintf

#include "./modules/include/color.h"
#include "./modules/include/fetchme.h"

/*
 * the current state:
 *
 * - Feature improvements being worked on.
 *
 */

int
main(int argc, char *argv[])
{
	if (argc > 1) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
			case 'v':
				printf("%s version %s\n", _PACKAGE_NAME, _PACKAGE_VERSION);
				break;
			case 'h': /* fall through */
			default:
				fprintf(stderr,
						"Usage: \n"
						"\tfetchme [ -v ]\t\tPrint version info\n"
						"\tfetchme [ -h ]\t\tPrint this help message\n"
						"\tfetchme [ no options ]\tPrint system info\n"
						"\n\tFor more help, please consult the man page.\n");
				break;
			}
		}
		return 0;
	}
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
