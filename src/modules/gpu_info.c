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

    printf("%s", color_distro());
    printf("GPU:\033[0m ");

    /* the following lines are simply to remove brackets, */

            for (size_t i = 0; i < strlen(namebuf); i++) {

                if (!(namebuf[i] == '[' || namebuf[i] == ']')) {
                    putchar(namebuf[i]);
                }
            }
    /* brackets are now removed. print the newline and exit. */
    putchar('\n');
    
    
        }
    }
    pci_cleanup(pciaccess);
    return EXIT_SUCCESS;
}
