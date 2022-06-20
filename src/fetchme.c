#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>

#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <sys/stat.h>

#include <pci/pci.h>


#include <pwd.h>

/* the current state:
 * - bug and CVE patching needed. 
 * - extra feature requests put on pause
 * - code style rework
 */

int username_at_hostname() {
        char hostname_value[100];
        uid_t  uid;
        FILE *host = fopen("/etc/hostname", "r");
        if(host == NULL) {
                printf("No hostname found, exiting...\n");
                exit(EXIT_FAILURE);
        }
        fscanf(host, "%99s", hostname_value);
        //     ^file  ^str   ^str value saved in variable
        fclose(host);
        struct passwd *pwd;

        if ((pwd = getpwuid(uid = geteuid())) == NULL) {
            perror("getpwuid() error");
            exit(EXIT_FAILURE);
        }
        else {
            printf("\033[1;36m%s\033[0m@\033[1;36m%s\033[0m\n", \
			pwd->pw_name, hostname_value);

	        int hostname_len = \
		    (strlen(pwd->pw_name) + strlen(hostname_value));

	        char line[hostname_len+1];

	        for (int i= 0; i < hostname_len+1; i++) line[i] = '~';
            line[(hostname_len+1)] = '\0';

	        printf("\033[1;36m%s\033[0m\n", line);
    }
    return EXIT_SUCCESS;

}

	


int distro() { 
	struct utsname buffer;

	char os_name[50];
	
    errno = 0;
    if (uname(&buffer) < 0) {
		perror("uname");
		exit(EXIT_FAILURE);
	}

	FILE *os_release = fopen("/etc/os-release", "r");

	if(os_release == NULL) {
	    printf("OS release NULL\n");
		exit(EXIT_FAILURE);
	}

    fscanf(os_release, "NAME=%49[^\n]+", os_name);  // get everything 
                                                    // that isn't a 
                                                    // newline 
    fclose(os_release);
    /*
     * remove quotation marks from
     * os name if needed.
     */
    if (os_name[0] == '"') {
        char os_temp[50];
        sscanf(os_name, "\"%49[^\"]+", os_temp);
    /*
     * could be implemented better with
     * a strncpy of os_temp into os_name 
     * to have no else statement
     */
        printf("\033[1;36mOS:\033[0m %s %s\n", \
                os_temp, buffer.machine);
    }
    else {
        printf("\033[1;36mOS:\033[0m %s %s\n", \
                os_name, buffer.machine);
    }



    return EXIT_SUCCESS;
}

int kernel() {
	struct utsname buffer;
    errno = 0;
    if (uname(&buffer) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
		}
	printf("\033[1;36mKernel:\033[0m %s\n", buffer.release);
		
    return EXIT_SUCCESS;

}


int cpu_info() {
	FILE *cpu = fopen("/proc/cpuinfo", "r");
	if (cpu == NULL) {
		printf("cpuinfo not found\n");
		exit(EXIT_FAILURE);
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
	for (int i = 0; i < 4; i++) {
		while ((c = fgetc(cpu)) != '\n' && c != EOF);
	} // skip lines 1-4; we don't need them

	fgets(p1line, sizeof(p1line), cpu);
	sscanf(p1line, "%*9s %*9s \t: %9s %9s %9s %9s", \
            p1_value1, p1_value2, p1_value3, p1_value4);

	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);

	fgets(p2line, sizeof(p2line), cpu);
	sscanf(p2line, "%*9s %*9s \t: %9s", p2_value1);

	while ((c = fgetc(cpu)) != '\n' && c != EOF);
	while ((c = fgetc(cpu)) != '\n' && c != EOF);

	fgets(p3line, sizeof(p3line), cpu);
	sscanf(p3line, "%*9s \t: %9s", p3_value1);

	fclose(cpu);
	
	printf("\033[1;36mCPU:\033[0m %s %s %s %s (%s) @ %sMHz\n",\
            p1_value1, p1_value2, p1_value3, p1_value4, p3_value1, p2_value1);
    return EXIT_SUCCESS;
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
        pci_lookup_name(pciaccess, namebuf, sizeof(namebuf), \
            PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
      
        if (((strncmp(&namebuf[7], "GeForce", 7)) == 0) || ((strncmp(&namebuf[0], "Radeon RX", 9)) == 0))
      		printf("\033[1;36mGPU:\033[0m %s\n", namebuf);
    }
    pci_cleanup(pciaccess);
    return EXIT_SUCCESS;
}
int memory_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if(fp == NULL) {
        printf("Unable to return meminfo\n");
        exit(EXIT_FAILURE);
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
// TODO: replace fgets-scanf with fscanf

    fgets(line1, sizeof(line1), fp);
    sscanf(line1, "%*99s %99s", line1_value);

    fgets(line2, sizeof(line2), fp);
    sscanf(line2, "%*99s %99s", line2_value);

    fgets(line3, sizeof(line3), fp);
    sscanf(line3, "%*99s %99s", line3_value);

    fgets(line4, sizeof(line4), fp);
    sscanf(line4, "%*99s %99s", line4_value);

    fgets(line5, sizeof(line5), fp);
    sscanf(line5, "%*99s %99s", line5_value);

    int c;
	for (int i = 0; i < 15; i++) {
	    while ((c = fgetc(fp)) != '\n' && c != EOF);
	}
    fgets(line21, sizeof(line21), fp);
    sscanf(line21, "%*99s %99s", line21_value);

// TODO: get rid of this mess used to skip lines

    while ((c = fgetc(fp)) != '\n' && c != EOF);
    while ((c = fgetc(fp)) != '\n' && c != EOF);
                
    fgets(line24, sizeof(line24), fp);
    sscanf(line24, "%*99s %99s", line24_value);

    fclose(fp);
    int x;
    sscanf(line1_value, "%d", &x); //convert char to int

    int TOTAL_RAM = (x/1000/1000);
/* TODO: better and more 
 * descriptive variable names */
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

    int MorG;                  // use MiB or GiB
    if (USED_RAM < 1) {
        MorG = 'M';
        USED_RAM = (USED_RAM * 1000);
    }
    else {
        MorG = 'G';
    }
        printf("\033[1;36mMemory:\033[0m %.1f%c/%dG\n", \
                USED_RAM, MorG, TOTAL_RAM);

    return EXIT_SUCCESS;
}

int main() {

        username_at_hostname();
        distro();
        kernel();
        cpu_info();
        gpu_info();
        memory_info();
     return 0;
}
