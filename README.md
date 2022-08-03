## fetchme
Rewrite of fetchme-bash in C99. Similiar to neofetch, but in C, so it should be able to do more.
<img src="https://user-images.githubusercontent.com/72793802/177895040-738fffa7-4ce1-4a70-b3e1-e6413702f2b6.png" align="right">

download with:

``git clone https://github.com/Connor-GH/fetchme``

compile with:

``cd fetchme``

# [Do you want to compile with gcc?]

``make CC=gcc -j$(nproc) bin/fetchme``

# [Do you want to compile with clang?]

``make CC=clang -j$(nproc) fetchme``

or to install it to /usr/bin:

``make CC=gcc-or-clang -j$(nproc) fetchme && sudo make install``

reinstall:
``make remove CC=gcc-or-clang -j$(nproc) fetchme && sudo make uninstall && sudo make install``

# debugging (or for development):

``make CC=gcc-or-clang DEBUG=true -j$(nproc) remove check fetchme`` (requires cppcheck and clang/gcc)


read the changelog
<a href="docs/CHANGELOG.md">here</a>

# Dependencies:
- clang or gcc (debugging requires clang and cppcheck; optionally requires valgrind, gdb, etc)

[Resolution detection]
- libx11

[Refresh Rate detection]
- libxrandr

[GPU detection]
- libpci
