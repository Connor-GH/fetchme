## Code Style

# This project follows the Linux/coreboot code style:
https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/Documentation/process/coding-style.rst
https://doc.coreboot.org/contributing/coding_style.html

# ...With a couple differences.
- indentations/tabs are 4 spaces
- headers go in a specific order: standard libraries, POSIX libraries, system libraries, then X11 libraries. (alphabetical order if there are multiple of one type)
- a little pedantic, but all int functions on success must ``return EXIT_SUCCESS;`` if they would otherwise ``return 0;``. This is more portable. (the same is true for ``exit(EXIT_FAILURE);`` and a nonzero value)
