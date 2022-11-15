## Changelog
- improved GPU detection - the speed of GPU detection has increased.

# older changes

Improved GPU detection - ALL gpus are now detected.

Improved shell detection - shell is now detected from the environment variable instead of using ``unistd.h``

Added automatic man page installation/uninstallation

Improved memory usage detection to be more accurate (now there is a ~1% delta between ``free -h --si`` and this program)

added gentoo package count detection using ``glob()``

improved the config to be Makefile variables instead of C header macros.

added the ability to only link and compile files that are specified in the config. (leads to small and fast binaries)

changed license to the (GPLv3-compatible) Apache License, Version 2.0.

added automatic color detection based on distro

added ``CUSTOM_COLOR`` and ``CUSTOM_COLOR_VALUE`` macros to replace the ``COLOR`` macro

removed every Variable Length Array (hooray!)

upgraded default build optimization to ``-O2`` with ``-flto``

moved some debugging features to DEBUG=true instead of being default in the build.



The project's code style guidelines will be posted if requested.
