TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin


TARGET 	 =  fetchme


CFLAGS	 =  -std=c99 -march=native -O2 -flto -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR)

WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold
WGCC  += -Wformat-security -Wstack-protector

WCLANG = -Weverything

WFLAGS = -Wall -Wextra -Wpedantic \
         -Wshadow -Wvla -Wpointer-arith -Wwrite-strings -Wfloat-equal \
         -Wcast-align -Wcast-qual -Wbad-function-cast \
         -Wstrict-overflow=4 -Wunreachable-code -Wformat=2 \
         -Wundef -Wuninitialized -Wsign-compare
WNOFLAGS=-Wno-unknown-pragmas

LFLAGS	 =	-Wall $(IVAR) -flto -lpci -lX11 -lXrandr -lm
# detect if the user chose GCC or Clang
ifeq ($(CC),gcc)

	CC  	= gcc
	CFLAGS += $(WGCC)
	LINKER 	= gcc

ifeq ($(DEBUG),true)
	WGCC   += -fanalyzer -fcf-protection=full -D_FORTIFY_SOURCE=2 -fstack-clash-protection
	CFLAGS	= -std=c99 -march=native -g -Og -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR) $(WGCC)

endif #debug

else ifeq ($(CC),clang)

	CC  	= clang
	CFLAGS += $(WCLANG)
	LINKER 	= clang

ifeq ($(DEBUG),true)
	LFLAGS += -fsanitize=address
	WCLANG += -fsanitize=undefined,signed-integer-overflow,null,alignment,address,leak \
			  -fsanitize-undefined-trap-on-error -fno-omit-frame-pointer -fstack-clash-protection
	CFLAGS	= -std=c99 -march=native -g -Og -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR) $(WCLANG)
endif #debug

endif #compiler

SRCDIR   = 	src
OBJDIR   = 	obj
BINDIR   = 	bin

SOURCES :=  $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/modules/*.c)
INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       =  rm -rf



$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LFLAGS) -o $(BINDIR)/$@
	@strip $(BINDIR)/$(TARGET)
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
