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
#include <pwd.h>
int username() {
struct passwd *p;
uid_t  uid;

if ((p = getpwuid(uid = geteuid())) == NULL)
	perror("getpwuid() error");
else {
  printf("%s",       p->pw_name);
  }
}
int usershell() {
	struct passwd *p;
	uid_t  uid;

	if ((p = getpwuid(uid = geteuid())) == NULL)
		        perror("getpwuid() error");
	else {
	printf("Shell ~ %s\n",       p->pw_shell);
	}
}
int hstnme() {
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
	printf("@%s\n~~~~~~~~~~~\n", hostname_value);
}
	int main(int argc, char** argv, char** envp) {
		struct utsname buffer;
	errno = 0;
	if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
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
              int64_t x;
              	sscanf(line1_value, "%lld", &x); //convert char to int //total
              int TOTAL_RAM = (x/1000/1000);
              int64_t y;
              	sscanf(line2_value, "%lld", &y); //memfree
              int64_t z;
              	sscanf(line3_value, "%lld", &z); //available
              int64_t z1;
              	sscanf(line4_value, "%lld", &z1); //buffers
              int64_t z2;
              	sscanf(line5_value, "%lld", &z2); //cache
              int64_t z3;
              	sscanf(line21_value, "%lld", &z3); //shmem
              int64_t z4;
              	sscanf(line24_value, "%lld", &z4); //reclaimable
              float USED_RAM = (x + z3 - y - z1 - z2 - z4)/1024./1024.;
         int MorG;
         if ("%.2f", USED_RAM < 1) {
            MorG = 'M';   
	 USED_RAM = (USED_RAM * 1000);
            printf("%.0f%c/%dG\n", USED_RAM, MorG, TOTAL_RAM);
            }
         else {
            MorG = 'G';
            printf("%.1f%c/%dG\n", USED_RAM, MorG, TOTAL_RAM);
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
	printf("Uptime ~ %d hours, %d mins\n", uptime_h_i, min);

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

printf("Packages ~ %zu\n", count-1);
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
        }
    else
	printf("Terminal ~ %s\n", terminal_emulator);
}

int cpu_info() {
FILE *cpu = fopen("/proc/cpuinfo", "r");
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
printf("CPU ~ %s %s %s %s (%s) @ %sMHz\n", p1_value1, p1_value2, p1_value3, p1_value4, p3_value1, p2_value1);
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
      if ((strncmp(&namebuf[0], "Radeon RX", 9)) == 0)
      printf("GPU ~ %s\n", namebuf);
      else if ((strncmp(&namebuf[7], "GeForce", 7)) == 0)
      printf("GPU ~ %s\n", namebuf);
      else {
      printf("");
    }
}
  pci_cleanup(pciaccess);
				           return 0;
}

	username();
	hstnme();
	printf("OS ~ %s %s %s\n", buffer.nodename, buffer.sysname, buffer.machine);
	printf("Kernel ~ %s\n", buffer.release);
	uptime1();
	pkgcnt();
	usershell();
	term(envp);
	cpu_info();
	gpu_info();
	printf("Mem ~ ");
	mem();

       return EXIT_SUCCESS;
	}
