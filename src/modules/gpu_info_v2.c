#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pci/pci.h>

#include "./include/fetchme.h"

int
gpu_info_v2(const char *color_distro)
{
#if UNIX_SUPPORT
	struct pci_dev *dev;
	struct pci_access *pciaccess;
	char *pci_ids_value = malloc(sizeof(char) * 128);
	char *dev_string;
	int device;
	size_t len;
	int c = 0;
	char *src = NULL;
	char *dest = NULL;
	FILE *pci_ids;

	pciaccess = pci_alloc();
	pci_init(pciaccess);
	pci_scan_bus(pciaccess);
	for (dev = pciaccess->devices; dev; dev = dev->next) {
		/*
         * We can use a shortcut here. if pci_read_word(dev,PCI_CLASS_DEVICE)
         * is 768, we know that a result of pci_lookup_name will be
         * VGA Compatable Controller; therefore, we can save a
         * call to pci_lookup_name. The same logic can be applied
         * for vendor_id and device_id, bit it would require a
         * large lookup table for the numbers. At that point, it
         * is easier just to call the function.
         */
		/* tell the compiler that the device is likely not 768 (x != 0x300) */
		if (likely(pci_read_word(dev, PCI_CLASS_DEVICE) != 768))
			continue;

		device = pci_read_word(dev, PCI_DEVICE_ID);
		len = (size_t)snprintf(NULL, 0, "%x", device);
		pci_ids = fopen("/usr/share/hwdata/pci.ids", "r");

		dev_string = malloc(sizeof(char) * (len + 1));
		snprintf(dev_string, len + 1, "%x", device);

		if (pci_ids == NULL) {
			pci_ids = fopen("/usr/share/pci.ids", "r");
			if (pci_ids == NULL)
				pci_ids = fopen("/usr/share/misc/pci.ids", "r"); // Debian
			if (pci_ids == NULL)
				pci_ids = fopen("/var/lib/pciutils/pci.ids", "r");
#if BSD_SUPPORT_ONLY
			if (pci_ids == NULL)
				pci_ids =
					fopen("/usr/local/share/pciids/pci.ids", "r"); // FreeBSD
			if (pci_ids == NULL)
				pci_ids = fopen("/var/share/misc/pci_vendors", "r");
#endif
			if (pci_ids == NULL) {
				perror("pci.ids");
				exit(EXIT_FAILURE);
			}
		}

		while (c != EOF) {
			fscanf(pci_ids, "%127s", pci_ids_value); /* get the line */
			if (strcmp(dev_string, pci_ids_value) == 0)
				break; /* we have our value */

			fscanf(pci_ids, "%127s", pci_ids_value); /* keep searching */
			c = fscanf(pci_ids, "%*[^\n]\n"); /* move to another line */
		}
		free(dev_string);
		/*
         * we have the proper ID.
         * Get the whole line (GPU name).
         */
		fscanf(pci_ids, "\t%127[^\n]", pci_ids_value);
		fclose(pci_ids);

		/* the following lines remove brackets */
		src = dest = pci_ids_value;
		while (*src != '\0') {
			if (!(*src == '[' || *src == ']')) {
				*dest = *src; /* copy the char at src to dest */
				dest++;
			}
			src++; /* increment source pointer */
		}
		*dest = '\0'; /* terminate string with NUL */

		printf("%sGPU:\033[0m %s\n", /* print the final result */
			   color_distro, pci_ids_value);
		free(pci_ids_value);

		pci_cleanup(pciaccess);
		return EXIT_SUCCESS;
	}
	pci_cleanup(pciaccess);
	fprintf(stderr, "Unable to find GPU\n");
	exit(EXIT_FAILURE);
#else
	return EXIT_SUCCESS;
#endif
}
