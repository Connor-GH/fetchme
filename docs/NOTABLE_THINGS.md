## Things to note:

the 'packages' function currently only works with pacman, pkg, apk, and portage distros. simply comment it out in the config.

if you are in a VM and you use an uneven amount of threads, QEMU will default to 11 sockets, 1 core. therefore, it is not a bug when it only shows 1 thread. and no, i can't fix it.

Terminal detection is entirely dependant on what ``$TERM`` is set to. If it is not set correctly on your terminal, encourage the developers to fix this. Asking about terminfo is a decent start.
