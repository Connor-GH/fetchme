## Things to note:

the 'packages' function currently only works with arch. simply comment it out in the config.

your gpu may not be detected correctly (but it should). if it isn't, make an issue.

if you are in a VM and you use an uneven amount of threads, QEMU will default to 11 sockets, 1 core. therefore, it is not a bug when it only shows 11 threads. and no, i can't fix it.

terminal detection is entirely dependant on what ``$TERM`` is set to. if it is not set correctly on your terminal, encourage the developers to fix this.
