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
	pciaccess->id_lookup_mode = PCI_LOOKUP_CACHE;

	for (dev = pciaccess->devices; dev; dev = dev->next) {
		dev->device_class = pci_read_word(dev, PCI_CLASS_DEVICE);

		/*
         * We can use a shortcut here. if dev->device_class is
         * 768, we know that a result of pci_lookup_name will be
         * VGA Compatable Controller; therefore, we can save a
         * call to pci_lookup_name. The same logic can be applied
         * for vendor_id and device_id, bit it would require a
         * large lookup table for the numbers. At that point, it
         * is easier just to call the function.
         */
		if (dev->device_class != 768)
			continue;

		/* only fill in the info that we need to */
		pciaccess->id_lookup_mode = PCI_LOOKUP_DEVICE;
		pci_fill_info(dev, PCI_FILL_IDENT);

		pci_lookup_name(pciaccess, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE,
						dev->vendor_id, dev->device_id);

		/* the following lines remove brackets */
		src = dest = namebuf;
		while (*src != '\0') {
			if (!(*src == '[' || *src == ']')) {
				*dest = *src; /* copy the char at src to dest */
				dest++;
			}
			src++; /* increment source pointer */
		}
		*dest = '\0'; /* terminate string with NUL */

		printf("%sGPU:\033[0m %s\n", /* print the final result */
			   color_distro(), namebuf);

		pci_cleanup(pciaccess);
		return EXIT_SUCCESS;
	}
	pci_cleanup(pciaccess);
	fprintf(stderr, "Unable to find GPU\n");
	exit(EXIT_FAILURE);
}
