## Changelog

- removed every Variable Length Array (hooray!)
- fixed a (rather useless) format specifier "bug" in package_count.c 
- upgraded default build optimisation to -O3
- moved some debugging features to DEBUG=true instead of being default in the build.

The project's code style guidelines will be posted if requested.

# older changes

codebase moved to c99 instead of gnu99

Dependencies to X have been added back (but are not needed if you disable the modules in the config and edit the makefile).
These dependencies were for the display size and refresh rate modules. (You will still need the libpci dependency to get GPU detection.)

Codebase sorting and build toolchain mostly complete. (This means getting rid of bugs and security issues, 
whilst making the code more readable.)
