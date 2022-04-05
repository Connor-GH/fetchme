#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <pci/pci.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <pwd.h>


int usershell() {
	struct passwd *p;
	uid_t  uid;

	if ((p = getpwuid(uid = geteuid())) == NULL) {
		        perror("getpwuid() error");
	return -1;
	}
	else {
	printf("\033[1;36msh ~\t\033[0m %s\n", p->pw_shell);
	return 0;
	}
}

int username_at_hstnme() {
	FILE *host = fopen("/etc/hostname", "r");
	if(host == NULL) {
		printf("No hostname found, exiting...\n");
		return -1;
			}
	char hostname[200];
	char hostname_value[100];
	fgets(hostname, sizeof(hostname), host);
	sscanf(hostname, "%100s", hostname_value);
	fclose(host);
	struct passwd *p;
	uid_t  uid;

	if ((p = getpwuid(uid = geteuid())) == NULL) {
		        perror("getpwuid() error");
	return -1;
	}
	else {
	printf("\033[1;36m%s\033[0m@\033[1;36m%s\033[0m\n", p->pw_name, hostname_value);
	return 0;
	}

}

int OS_() {
		struct utsname buffer;
	errno = 0;
	if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
	}
	FILE *opsys = fopen("/etc/os-release", "r");
	if(opsys == NULL) {
		printf("OS release NULL\n");
		return -1;
	}
	char pretty_name[50];
	char pretty_name_value[20];
	char pretty_name_value1[20];    	// temporary value
	char pretty_name_value_fixed[6];	//real value
		fgets(pretty_name, sizeof(pretty_name), opsys);
		sscanf(pretty_name, "%20s %20s", pretty_name_value, pretty_name_value1);
	fclose(opsys);
	if(pretty_name_value[0] == 'N')
		memmove(pretty_name_value, pretty_name_value+6, strlen(pretty_name_value));
	
	memset(pretty_name_value_fixed, '\0', sizeof(pretty_name_value_fixed));  //normal C stuff, but magic for me. 
	strncpy(pretty_name_value_fixed, pretty_name_value1, 5);		 //Whole string is copied and safely "shrunk" in this new value


	printf("\033[1;36mos ~\t\033[0m %s %s %s\n", pretty_name_value, pretty_name_value_fixed, buffer.machine);

	return EXIT_SUCCESS;
}

int KRNL() {
	struct utsname buffer;
        errno = 0;
        if (uname(&buffer) < 0) {
                perror("uname");
                exit(EXIT_FAILURE);
			        }
	printf("\033[1;36mkrnl ~\t\033[0m %s\n", buffer.release);
		
		return EXIT_SUCCESS;

}

int mem() {
        FILE *fp = fopen("/proc/meminfo", "r");
        if(fp == NULL) {
        printf("Unable to return meminfo\n");
               return -1;
        }
        char line1_value[100];
        char line2_value[100];
        char line3_value[100];
        char line4_value[100];
        char line5_value[100];
        char line21_value[100];
        char line24_value[100];
        char line1[200];
        char line2[200];
        char line3[200];
        char line4[200];
        char line5[200];
        char line21[200];
        char line24[200];
	// read line 1
        fgets(line1, sizeof(line1), fp);
        // read name and value
        sscanf(line1, "%*100s %100s", line1_value);
   //read line 2
        fgets(line2, sizeof(line2), fp);
        sscanf(line2, "%*100s %100s", line2_value);
           // read line 3
        fgets(line3, sizeof(line3), fp);
             // read name and value
        sscanf(line3, "%*100s %100s", line3_value);
        fgets(line4, sizeof(line4), fp);
        sscanf(line4, "%*100s %100s", line4_value);
        fgets(line5, sizeof(line5), fp);
																	
	sscanf(line5, "%*100s %100s", line5_value);
        int c;
	        		while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
			        while ((c = fgetc(fp)) != '\n' && c != EOF);
	        fgets(line21, sizeof(line21), fp);
			        sscanf(line21, "%*100s %100s", line21_value);
		                while ((c = fgetc(fp)) != '\n' && c != EOF);
		                while ((c = fgetc(fp)) != '\n' && c != EOF);
	        fgets(line24, sizeof(line24), fp);
                sscanf(line24, "%*100s %100s", line24_value);
  fclose(fp);
              int x;
              	sscanf(line1_value, "%d", &x); //convert char to int //total
              int TOTAL_RAM = (x/1000/1000);
              int y;
              	sscanf(line2_value, "%d", &y); //memfree
              int z;
              	sscanf(line3_value, "%d", &z); //available
              int z1;
              	sscanf(line4_value, "%d", &z1); //buffers
              int z2;
              	sscanf(line5_value, "%d", &z2); //cache
              int z3;
              	sscanf(line21_value, "%d", &z3); //shmem
              int z4;
              	sscanf(line24_value, "%d", &z4); //reclaimable
              float USED_RAM = (x + z3 - y - z1 - z2 - z4)/1024./1024.;
         int MorG;
         if (USED_RAM < 1) {
            MorG = 'M';   
	 USED_RAM = (USED_RAM * 1000);
            printf("\033[1;36mmem ~\t\033[0m %.0f%c/%dG\n", USED_RAM, MorG, TOTAL_RAM);
	    return 0;
            }
         else {
            MorG = 'G';
            printf("\033[1;36mmem ~\t\033[0m %.1f%c/%dG\n", USED_RAM, MorG, TOTAL_RAM);
	    return 0;
            }
}
int uptime1() {
	FILE *up = fopen("/proc/uptime", "r");
        	if (up == NULL) {
			return -1;
			printf("No uptime found, exiting");
			}
	char upline[100];
	char upline_value[100];
	fgets(upline, sizeof(upline), up);
	sscanf(upline, "%100s %*100s", upline_value);
	fclose(up);
	float upline_value_f;
	sscanf(upline_value, "%f", &upline_value_f);
		float uptime_hours = (upline_value_f / 3600);
		int uptime_h_i = upline_value_f / 3600;
		int min = (uptime_hours - uptime_h_i) * 60;
	printf("\033[1;36mup ~\t\033[0m %d hours, %d mins\n", uptime_h_i, min);
	return 0;

}
	
int pkgcnt(void) {
	size_t count = 0;
   struct dirent *res;
       struct stat sb;
    const char *path = "/var/lib/pacman/local";

       if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        DIR *folder = opendir(path);

       if (access (path, F_OK) != -1 ) {
       if (folder) {
       while ((res = readdir(folder))) {
       if (strcmp(res->d_name, ".") && strcmp(res->d_name, ".." )) {
       count++;
       }
    }

       closedir(folder);
    }
 else {
      perror ("Could not open the directory");
      exit(EXIT_FAILURE);
      }
     }
   }
 	else {
  		printf("The %s it cannot be opened or is not a directory\n", path);
  		exit (EXIT_FAILURE);
  }

	printf("\033[1;36mpkgs ~\t\033[0m %zu\n", count-1);
	return 0;
}
char* term(char* const* envp) {
 	char* terminal_emulator = NULL;

     for (size_t i = 0; envp[i] != NULL; i += 1) {
        char* eq = strchr(envp[i], '=');
     assert(eq != NULL);
         *eq = '\0';

     if (strcmp(envp[i], "TERM") == 0) {
           terminal_emulator = eq + 1;
      }
    *eq = '=';
      }
    if (terminal_emulator == NULL) {
      puts("wrong ENV var directory");
      exit(EXIT_FAILURE);
        }
    else {
	printf("\033[1;36mterm ~\t\033[0m %s\n", terminal_emulator);
    return 0;
    }
}

int cpu_info() {
	FILE *cpu = fopen("/proc/cpuinfo", "r");
	if (cpu == NULL) {
		printf("cpuinfo not found");
		return -1;
		}
	char p1line[200];
	char p1_value1[10];
	char p1_value2[10];
	char p1_value3[10];
	char p1_value4[10];
	char p2line[200]; //cpu freq line
	char p2_value1[10]; //cpu frequency
	char p3line[200]; //cpu thread line
	char p3_value1[10]; //cpu threads
	
	int c;
	while ((c = fgetc(cpu)) != '\n' && c != EOF); // skip lines 1-4; we don't need them
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	fgets(p1line, sizeof(p1line), cpu);
		sscanf(p1line, "%*10s %*10s \t: %10s %10s %10s %10s", p1_value1, p1_value2, p1_value3, p1_value4);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	fgets(p2line, sizeof(p2line), cpu);
		sscanf(p2line, "%*10s %*10s \t: %10s", p2_value1);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	fgets(p3line, sizeof(p3line), cpu);
		sscanf(p3line, "%*10s \t: %10s", p3_value1);
	fclose(cpu);
	
	printf("\033[1;36mcpu ~\t\033[0m %s %s %s %s (%s) @ %sMHz\n", p1_value1, p1_value2, p1_value3, p1_value4, p3_value1, p2_value1);
	return 0;
}
int gpu_info() {
	struct pci_access* pciaccess;
        struct pci_dev* dev;
        char namebuf[1024];
      pciaccess = pci_alloc();
      pci_init(pciaccess);
      pci_scan_bus(pciaccess);
      for(dev = pciaccess->devices; dev; dev = dev->next) {
      pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
      pci_lookup_name(pciaccess, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
      
      if (((strncmp(&namebuf[7], "GeForce", 7)) == 0) || ((strncmp(&namebuf[0], "Radeon RX", 9)) == 0))
      		printf("\033[1;36mgpu ~\t\033[0m %s\n", namebuf);
		else { }
 }
  pci_cleanup(pciaccess);
  return 0;
}
int screenres() {
	Display *dpy;
	XRRScreenResources *screen;
	XRRCrtcInfo *crtc_info;

	dpy = XOpenDisplay(":0");
	screen = XRRGetScreenResources (dpy, DefaultRootWindow(dpy));

	crtc_info = XRRGetCrtcInfo (dpy, screen, screen->crtcs[0]);
	XRRFreeScreenResources(screen);
	XCloseDisplay(dpy);
	if (crtc_info->mode == None)
		return -1;
	RRMode active_mode_id = crtc_info->mode;
	float active_rate;
	for (int i = 0; i < screen->nmode; ++i) {
	//for (int i = screen->nmode; i--;) {
	
		XRRModeInfo mode_info = screen->modes[i];
		
	if (mode_info.id == active_mode_id)
	
		active_rate = (float)mode_info.dotClock / ((float)mode_info.hTotal * (float)mode_info.vTotal);
	}


	printf("\033[1;36mres ~\t\033[0m %dx%d @ %.2fHz\n", crtc_info->width, crtc_info->height, active_rate);
	XRRFreeCrtcInfo(crtc_info);
	return 0;
}

int main(int argc, char** argv, char** envp) {
printf("\033[1;36m                   -`			"); username_at_hstnme();
printf("\033[1;36m                  .o+`			~~~~~~~~~~~\033[0m\n");
printf("\033[1;36m                 `ooo/			"); OS_();
printf("\033[1;36m                `+oooo:			"); KRNL();
printf("\033[1;36m               `+oooooo:		"); uptime1();
printf("\033[1;36m               -+oooooo+:		"); pkgcnt();
printf("\033[1;36m             `/:-:++oooo+:		"); usershell();
printf("\033[1;36m            `/++++/+++++++:		"); screenres();
printf("\033[1;36m           `/++++++++++++++:		"); term(envp);
printf("\033[1;36m          `/+++ooooooooooooo/`		"); cpu_info();
printf("\033[1;36m         ./ooosssso++osssssso+`		"); gpu_info();
printf("\033[1;36m        .oossssso-````/ossssss+`	"); mem();
printf("\033[1;36m       -osssssso.      :ssssssso.		\n");
printf("\033[1;36m      :osssssss/        osssso+++.		\n");
printf("\033[1;36m     /ossssssss/        +ssssooo/-		\n");
printf("\033[1;36m   `/ossssso+/:-        -:/+osssso+-		\n");
printf("\033[1;36m  `+sso+:-`                 `.-/+oso:		\n");
printf("\033[1;36m `++:.                           `-/+/	\n");
printf("\033[1;36m .`                                 `/	\n\033[0m");

       return EXIT_SUCCESS;
}
