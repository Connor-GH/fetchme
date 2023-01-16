WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold
WGCC  += -Wformat-security -Warray-bounds -Wstack-protector
WGCC  += -Wall -Wextra -Wpedantic -Wshadow -Wvla -Wpointer-arith -Wwrite-strings \
		 -Wfloat-equal -Wcast-align -Wcast-qual -Wbad-function-cast \
		 -Wunreachable-code -Wundef -Werror=format-security -Werror=array-bounds

WNOFLAGS= -Wno-unknown-pragmas -Wno-unused-result
VISIBILITY ?= -fvisibility=hidden

ifeq ($(RELEASE),true)
	F_CFLAGS = -march=x86-64 -O2
else
	F_CFLAGS = -march=native -O2
endif
LFLAGS  =

# detect if the user chose GCC or Clang

ifneq (,$(filter $(CC),gcc cc))

	CC  	= gcc
	LINKER 	?= gcc
	LTO 	= -flto
	STRIP	?= strip
ifeq ($(DEBUG),true)
	# gcc-specific security/debug flags
	WGCC   += -fanalyzer
	F_CFLAGS += -ggdb
endif #debug
F_CFLAGS += $(WGCC)
else ifeq ($(CC),clang)

	LINKER 	= clang
	LTO 	= -flto=thin
	AR		= llvm-ar
	NM		= llvm-nm
	OBJCOPY = llvm-objcopy
	STRIP 	?= llvm-strip

ifeq ($(DEBUG),true)
	# clang-specific security/debug flags
	F_CFLAGS += -fsanitize=undefined,signed-integer-overflow,null,alignment,address,leak,cfi \
			  -fsanitize-undefined-trap-on-error -ftrivial-auto-var-init=pattern \
			  -mspeculative-load-hardening -mretpoline
	LFLAGS  = -fsanitize=address
endif #debug
F_CFLAGS += -Weverything
WNOFLAGS += -Wno-disabled-macro-expansion
endif #compiler


ifeq ($(DEBUG),true)
	# generic security/debug flags
	F_CFLAGS += -Og -D_DEBUG -fno-builtin
	LFLAGS += -Wl,-z,relro,-z,noexecstack
endif # DEBUG
ifeq ($(RELEASE),true)
	F_CFLAGS += -fstack-clash-protection -D_FORTIFY_SOURCE=2 -fcf-protection \
			  -Werror=format-security
	LFLAGS += -fPIE -fPIC
endif

# Are we doing PGO?
ifeq ($(PGO),gen)
	F_CFLAGS += -fprofile-instr-generate -gline-tables-only -fcoverage-mapping
	LFLAGS += -fprofile-instr-generate
else ifeq ($(PGO),use)
	F_CFLAGS += -fprofile-instr-use=fetchme.profdata -gline-tables-only
	LFLAGS += -fprofile-instr-use=fetchme.profdata
endif
# build generic release


# Flags every compile will need
F_CFLAGS += -D_PACKAGE_NAME=\"$(TARGET)\" -D_PACKAGE_VERSION=\"$(VERSION)\" \
		  $(MODULES) -std=c99 -pipe $(LTO) $(WNOFLAGS) $(IVAR) $(VISIBILITY) $(CFLAGS)
LFLAGS += $(IVAR) $(LTO) $(M_LFLAGS) -L/usr/local/lib $(LDFLAGS)
