## fetchme
Rewrite of fetchme-bash in C99. Similiar to neofetch, but in C, so it should be able to do more.
<img src="https://user-images.githubusercontent.com/72793802/177895040-738fffa7-4ce1-4a70-b3e1-e6413702f2b6.png" align="right">

download with:

``git clone https://github.com/Connor-GH/fetchme``

compile with:

``cd fetchme``

# [Do you want to compile with gcc?]

``make CC=gcc bin/fetchme``

# [Do you want to compile with clang?]

``make CC=clang fetchme``

or to install it to /usr/bin:

``sudo make CC=gcc-or-clang fetchme install``

reinstall:
``sudo make clean CC=gcc=or-clang fetchme install``

debugging (or for development):
``make CC=clang DEBUG=true remove check fetchme`` (requires cppcheck and clang)
``make CC=gcc DEBUG=true remove check fetchme`` (requires cppcheck and gcc; worse at debugging)

read the changelog
<a href="docs/CHANGELOG.md">here</a>

# Dependencies:
- clang or gcc (debugging requires clang and cppcheck)
- libx11
- libpci
- libxrandr
