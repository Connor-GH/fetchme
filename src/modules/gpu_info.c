#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pci/pci.h>

#include "./include/gpu_info.h"
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

        if (((strncmp(&namebuf[7], "GeForce", 7)) == 0) || \
                ((strncmp(&namebuf[0], "Radeon RX", 9)) == 0)) {

            for(size_t i = 0; i < strlen(namebuf)-1; i++) {

                // extended ASCII "Non-breaking Space"
                if (namebuf[i] == '[') namebuf[i] = '\255';
            }
            sscanf(namebuf, "%1023[^]]", namebuf);
            printf(COLOR);
            printf("GPU:\033[0m %s\n", namebuf);
        }
    }
    pci_cleanup(pciaccess);
    return EXIT_SUCCESS;
}
