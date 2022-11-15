TOPDIR 	:=  ./src
IVAR 	:=  -I. -I$(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin

include config_backend.mk
TARGET 	 = fetchme
VERSION  = 1.4


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

CFLAGS	= -march=native -O2

LFLAGS  = -Wl,--strip-all -Wl,-O3

# detect if the user chose GCC or Clang
ifeq ($(CC),cc)
	CC		= gcc
	CFLAGS += $(WGCC)
	LINKER 	= gcc
	LTO 	= -flto -fno-fat-lto-objects
endif # CC

ifeq ($(CC),gcc)

	CC  	= gcc
	CFLAGS += $(WGCC)
	LINKER 	= gcc
	LTO 	= -flto -fno-fat-lto-objects
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
	LTO 	= -flto=thin

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
	LFLAGS += -fPIE -Wl,-z,relro -Wl,--as-needed -Wl,-z,now -Wl,-z,noexecstack
endif

CFLAGS += -D_PACKAGE_NAME=\"$(TARGET)\" -D_PACKAGE_VERSION=\"$(VERSION)\" \
		  $(MODULES) \
		  -std=c99 -pipe $(LTO) $(WFLAGS) $(WNOFLAGS) $(IVAR)
LFLAGS += $(IVAR) $(M_LFLAGS) $(LTO) -L/usr/local/lib -Wl,-rpath=/usr/local/lib



OBJDIR   = 	obj
BINDIR   = 	bin

INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       =  rm -rf

ifeq ($(PGO),gen)
	CFLAGS += -fprofile-instr-generate -gline-tables-only -fcoverage-mapping
	LFLAGS += -fprofile-instr-generate
else ifeq ($(PGO),use)
	CFLAGS += -fprofile-instr-use=fetchme.profdata -gline-tables-only
	LFLAGS += -fprofile-instr-use=fetchme.profdata
endif


$(TARGET):
	@# rebuild and build with just `make'
	$(MAKE) remove
	@# create these directories if needed
	mkdir -p obj/modules
	mkdir -p bin/
	@# compile with multiple threads, then link.
	@echo -e "\n\n\nCC =\t$(CC)"
	@echo -e "LD =\t$(LINKER)"
	@echo -e "CFLAGS =\t$(CFLAGS)\n\n\n"
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

format:
	@find . -iname *.h -o -iname *.c | xargs clang-format -style=file:.clang-format -i


pgo:
	@# only clang is supported for this PGO
	if [[ -f fetchme.profdata ]]; then \
		make CC=clang PGO=use && $(rm) fetchme.prof*; \
	else \
		make CC=clang PGO=gen && \
	for x in {0..100}; do \
		LLVM_PROFILE_FILE=fetchme.profraw ./bin/fetchme > /dev/null; \
	done; \
	llvm-profdata merge -output=fetchme.profdata fetchme.profraw; \
	fi
