#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pci/pci.h>

#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

int gpu_info() {
    struct pci_access* pciaccess;
    struct pci_dev* dev;
    char namebuf[1024];
    size_t i = 0;

    pciaccess = pci_alloc();
    pci_init(pciaccess);
    pci_scan_bus(pciaccess);

    for(dev = pciaccess->devices; dev; dev = dev->next) {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
        pci_lookup_name(pciaccess, namebuf, sizeof(namebuf) - 1, \
            PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);

        /* 
         * This will for SURE change in the future. 
         * It's awful that this is hardcoded but I will
         * come up with a better solution.
         */
        if (((strncmp(&namebuf[7], "GeForce", 7)) == 0) || \
                ((strncmp(&namebuf[0], "Radeon RX", 9)) == 0)) {

    printf(COLOR);
    printf("GPU:\033[0m ");

    /* the following 15 or so lines are simply to remove 
     * brackets, and it's for sure not the right way to do it. */

    while (i < strlen(namebuf)) {

        if (namebuf[i] == '[' || namebuf[i] == ']') {

            namebuf[i] = namebuf[i+1];
            i++; /*  in this case, we
                  *  continue the loop
                  *  but skip an iteration */
        }
        if (i == strlen(namebuf)-1) namebuf[i+1] = '\0';

        /* this does the same thing as 
         * printf("%c", namechar[i]);
         * and it's personal preference */
        putchar(namebuf[i]); 
        i++;
    }
    printf("\n");
    
        }
    }
    pci_cleanup(pciaccess);
    return EXIT_SUCCESS;
}
