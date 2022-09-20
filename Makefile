TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin

include config_backend.mk
TARGET 	 = fetchme
VERSION  = 1.3



WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold
WGCC  += -Wformat-security -Warray-bounds -Wstack-protector


WFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wvla -Wpointer-arith -Wwrite-strings \
		 -Wfloat-equal -Wcast-align -Wcast-qual -Wbad-function-cast -Wstrict-overflow=4 \
		 -Wunreachable-code -Wformat=2 -Wundef -Wuninitialized -Wsign-compare \
		 -Werror=format-security -Werror=array-bounds

WNOFLAGS= -Wno-unknown-pragmas -Wno-unused-result

CFLAGS	= -march=native -O2 -fno-exceptions -fno-asynchronous-unwind-tables

LFLAGS  = -Wl,--strip-all -Wl,-O3

# detect if the user chose GCC or Clang
ifeq ($(CC),gcc)

	CC  	= gcc
	CFLAGS += $(WGCC)
	LINKER 	= gcc

ifeq ($(DEBUG),true)
	# gcc-specific security/debug flags
	WGCC   += -fanalyzer 
	CFLAGS	= -ggdb $(WGCC)
	LFLAGS  =

endif #debug

else ifeq ($(CC),clang) # clang can be marginally slower

	CC  	= clang
	CFLAGS += -Weverything 
	LINKER 	= clang
	WNOFLAGS += -Wno-disabled-macro-expansion

ifeq ($(DEBUG),true)
	# clang-specific security/debug flags
	WFLAGS += -fsanitize=undefined,signed-integer-overflow,null,alignment,address,leak,cfi \
			  -fsanitize-undefined-trap-on-error -ftrivial-auto-var-init=pattern \
			  -fvisibility=hidden
	CFLAGS	= -gdwarf-4 -Weverything -mspeculative-load-hardening -mretpoline
	LFLAGS  = -fsanitize=address
endif #debug

endif #compiler
ifeq ($(DEBUG),true)
	# generic security/debug flags
	CFLAGS += -O1 -march=x86-64 -g3
	WFLAGS += -fomit-frame-pointer -fstack-clash-protection -D_FORTIFY_SOURCE=2 \
			  -fcf-protection -fstack-protector-all -fexceptions -fasynchronous-unwind-tables \
			  -Werror=format-security -D_DEBUG -fno-builtin-malloc -fno-builtin-calloc -fno-builtin
	LFLAGS += -fPIE -pie -Wl,-z,relro -Wl,--as-needed -Wl,-z,now -Wl,-z,noexecstack
endif

CFLAGS += -D_PACKAGE_NAME=\"$(TARGET)\" -D_PACKAGE_VERSION=\"$(VERSION)\" \
		  $(MODULES) \
		  -std=c99 -pipe -m64 -flto $(WFLAGS) $(WNOFLAGS) $(IVAR)
LFLAGS += $(IVAR) $(M_LFLAGS) -flto


OBJDIR   = 	obj
BINDIR   = 	bin

INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       =  rm -rf

$(TARGET):
	@# rebuild and build with just `make'
	$(MAKE) remove
	@# create these directories if needed
	mkdir -p obj/modules
	mkdir -p bin/
	## compile with multiple threads, then link.
	$(MAKE) $(OBJECTS)
	$(MAKE) link

link: 
	$(LINKER) $(OBJECTS) $(LFLAGS) -o $(BINDIR)/$(TARGET)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"
.PHONY: clean


clean:
	$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: install

install:
	mkdir -p ${INSTALLBINDIR}
	cp -r $(BINDIR)/$(TARGET) ${INSTALLBINDIR}
	@echo "Executable installed!"
	mkdir -p /usr/share/man/man1
	cp docs/fetchme.1.bz2 /usr/share/man/man1/
	@echo "Man page installed!"


uninstall:
	$(rm) ${INSTALLBINDIR}/$(TARGET)
	@echo "Exectuable removed!"
	rm /usr/share/man/man1/fetchme.1.bz2
	@echo "Man page uninstalled!"
