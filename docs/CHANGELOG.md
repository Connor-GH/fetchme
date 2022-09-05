## Changelog
- Improved memory usage detection to be more accurate (now there is a ~1% delta between ``free -h --si`` and this program)
- added gentoo package count detection using ``glob()``

# older changes

improved the config to be Makefile variables instead of C header macros.
added the ability to only link and compile files that are specified in the config. (leads to small and fast binaries)

changed license to the (GPLv3-compatible) Apache License, Version 2.0.

added automatic color detection based on distro

added ``CUSTOM_COLOR`` and ``CUSTOM_COLOR_VALUE`` macros to replace the ``COLOR`` macro

removed some (harmless) compiler warnings about formatting with types that were ``size_t``

removed every Variable Length Array (hooray!)

fixed a (rather useless) format specifier "bug" in package_count.c 

upgraded default build optimisation to ``-O2`` with ``-flto``

moved some debugging features to DEBUG=true instead of being default in the build.


codebase moved to c99 instead of gnu99

Dependencies to X have been added back (but are not needed if you disable the modules in the config and edit the makefile).
These dependencies were for the display size and refresh rate modules. (You will still need the libpci dependency to get GPU detection.)

Codebase sorting and build toolchain mostly complete. (This means getting rid of bugs and security issues, 
whilst making the code more readable.)

The project's code style guidelines will be posted if requested.
