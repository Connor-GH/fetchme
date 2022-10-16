#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pci/pci.h>

#include "./include/fetchme.h"
#include "./include/color.h"

int
gpu_info()
{
	struct pci_access *pciaccess;
	struct pci_dev *dev;
	char namebuf[128];
    char *src = NULL;
    char *dest = NULL;


	pciaccess = pci_alloc();
	pci_init(pciaccess);
	pci_scan_bus(pciaccess);

	for (dev = pciaccess->devices; dev; dev = dev->next) {
		pci_fill_info(dev, PCI_FILL_IDENT);

		pci_lookup_name(pciaccess, namebuf, sizeof(namebuf) - 1,
						PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);

		if (((strstr(namebuf, "Graphics")) != NULL) /* Intel or AMD/ATI */
			|| ((strstr(namebuf, "QXL")) != NULL) /* QEMU QXL */
			|| ((strstr(namebuf, "Virtio GPU")) != NULL) /* QEMU Virtio */
			|| ((strstr(namebuf, "VMware SVGA")) != NULL) /* VMware */
			|| ((strstr(namebuf, "VirtualBox Graphics Adapter")) != NULL)
            || ((strstr(namebuf, "Radeon")) != NULL) /* AMD/ATI */
			|| ((strstr(namebuf, "Tesla")) != NULL) /* NVIDIA */
			|| ((strstr(namebuf, "Quadro")) != NULL) /* NVIDIA */
			|| ((strstr(namebuf, "GeForce")) != NULL)) { /* NVIDIA */

			printf("%sGPU:\033[0m ", color_distro());

			/* the following lines are simply to remove brackets, */
            src = dest = namebuf;
            while (*src != '\0') {
                if (*src != '[') {
                    *dest = *src;  // copy the char at source to destination
                    dest++;
                }
                src++;             // increment source pointer
                if (*src != ']') {
                    *dest = *src;
                    dest++;
                }
                src++;
            }
            *dest = '\0';          // terminate string with null terminator


            printf("%s\n", namebuf);
		}
	}
	pci_cleanup(pciaccess);
	return EXIT_SUCCESS;
}
