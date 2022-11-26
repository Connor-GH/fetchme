WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold
WGCC  += -Wformat-security -Warray-bounds -Wstack-protector
WGCC  += -Wall -Wextra -Wpedantic -Wshadow -Wvla -Wpointer-arith -Wwrite-strings \
		 -Wfloat-equal -Wcast-align -Wcast-qual -Wbad-function-cast \
		 -Wunreachable-code -Wundef -Werror=format-security -Werror=array-bounds

WNOFLAGS= -Wno-unknown-pragmas -Wno-unused-result

ifeq ($(RELEASE),true)
	CFLAGS = -march=x86-64 -O2
else
	CFLAGS = -march=native -O2
endif
LFLAGS  = -Wl,-O2,--strip-all

# detect if the user chose GCC or Clang
ifneq (,$(filter $(CC),gcc cc))

	CC  	= gcc
	LINKER 	= gcc -fuse-ld=gold
	LTO 	= -flto -fno-fat-lto-objects
ifeq ($(DEBUG),true)
	# gcc-specific security/debug flags
	WGCC   += -fanalyzer
	CFLAGS += -ggdb
	LFLAGS  =
endif #debug
CFLAGS += $(WGCC)
else ifeq ($(CC),clang)

	LINKER 	= clang -fuse-ld=lld
	LTO 	= -flto=thin

ifeq ($(DEBUG),true)
	# clang-specific security/debug flags
	WFLAGS += -fsanitize=undefined,signed-integer-overflow,null,alignment,address,leak,cfi \
			  -fsanitize-undefined-trap-on-error -ftrivial-auto-var-init=pattern \
			  -fvisibility=hidden
	CFLAGS += -gdwarf-4 -mspeculative-load-hardening -mretpoline
	LFLAGS  = -fsanitize=address
endif #debug
CFLAGS += -Weverything
WNOFLAGS += -Wno-disabled-macro-expansion
endif #compiler

ifeq ($(DEBUG),true)
	# generic security/debug flags
	CFLAGS += -Og
	WFLAGS += -fomit-frame-pointer -fstack-clash-protection -D_FORTIFY_SOURCE \
			  -fcf-protection -fstack-protector-all -fexceptions -fasynchronous-unwind-tables \
			  -Werror=format-security -D_DEBUG -fno-builtin
	LFLAGS += -fPIE -fPIC -Wl,-z,relro,-z,noexecstack
endif # DEBUG

# Are we doing PGO?
ifeq ($(PGO),gen)
	CFLAGS += -fprofile-instr-generate -gline-tables-only -fcoverage-mapping
	LFLAGS += -fprofile-instr-generate
else ifeq ($(PGO),use)
	CFLAGS += -fprofile-instr-use=fetchme.profdata -gline-tables-only
	LFLAGS += -fprofile-instr-use=fetchme.profdata
endif
# build generic release

# Flags every compile will need
CFLAGS += -D_PACKAGE_NAME=\"$(TARGET)\" -D_PACKAGE_VERSION=\"$(VERSION)\" \
		  $(MODULES) -std=c99 -pipe $(LTO) $(WNOFLAGS) $(IVAR)
LFLAGS += $(IVAR) $(M_LFLAGS) $(LTO) -L/usr/local/lib -Wl,-rpath=/usr/local/lib
