TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin

include config_backend.mk
TARGET 	 =  fetchme



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

CFLAGS	= $(MODULES) -D_PACKAGE_NAME=\"fetchme\" -D_PACKAGE_VERSION=\"0.1.2\" \
		  -std=c99 -march=native -O2 -flto -m64 -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR)

LFLAGS  = -Wall $(IVAR) $(M_LFLAGS) -flto -Wl,--strip-all -Wl,-O3

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
			  -fvisibility=hidden -mspeculative-load-hardening -mretpoline 
	CFLAGS	= -gdwarf-4 -Weverything -mspeculative-load-hardening
	LFLAGS  = -fsanitize=address
endif #debug

endif #compiler
ifeq ($(DEBUG),true)
	# generic security/debug flags
	CFLAGS += $(MODULES) -D_PACKAGE_NAME=\"fetchme\" -D_PACKAGE_VERSION=\"0.1\" \
			  -O1 -std=c99 -flto -march=x86-64 -g3 -m64 -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR)
	WFLAGS += -fomit-frame-pointer -fstack-clash-protection -D_FORTIFY_SOURCE=2 \
			  -fcf-protection -fstack-protector-all -fexceptions -fasynchronous-unwind-tables \
			  -Werror=format-security -D_DEBUG -fno-builtin-malloc -fno-builtin-calloc -fno-builtin
	LFLAGS += $(IVAR) $(M_LFLAGS) -flto -fPIE -pie -Wl,-z,relro -Wl,--as-needed -Wl,-z,now \
			  -Wl,-z,noexecstack
endif


OBJDIR   = 	obj
BINDIR   = 	bin

INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       =  rm -rf

$(TARGET):
	# rebuild and build with just `make'
	$(MAKE) remove
	# create these directories if needed
	mkdir -p obj/modules
	mkdir -p bin/
	# compile with multiple threads, then link.
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
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: install

install:
	mkdir -p ${INSTALLBINDIR}
	cp -r $(BINDIR)/$(TARGET) ${INSTALLBINDIR}
	@echo "Executable installed!"


uninstall:
	@$(rm) ${INSTALLBINDIR}/$(TARGET)
	@echo "Exectuable removed!"


# used only for debug and development
check:
	cppcheck -j`nproc` -q --clang --inconclusive --std=c99 --force --enable=warning,style,performance,portability $(SOURCES)
