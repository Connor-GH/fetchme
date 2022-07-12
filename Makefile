
TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin


TARGET 	 =  fetchme


CFLAGS	 =  -std=c99 -march=native -O2 -pipe $(WFLAGS) $(WNOFLAGS) $(IVAR)

# detect if the user chose GCC or Clang
ifeq ($(CC),gcc)

	CC 		= gcc
	CFLAGS += $(WGCC)
	LINKER 	= gcc

else ifeq ($(CC),clang)

	CC = clang
	CFLAGS += $(WCLANG)
	LINKER 	= clang

endif

WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -fanalyzer
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold

WCLANG = -Weverything

WFLAGS = -Wall -Wextra -Wpedantic \
         -Wshadow -Wvla -Wpointer-arith -Wwrite-strings -Wfloat-equal \
         -Wcast-align -Wcast-qual -Wbad-function-cast \
         -Wstrict-overflow=4 -Wunreachable-code -Wformat=2 \
         -Wundef -Wuninitialized -Wsign-compare 
WNOFLAGS= \
		 -Wno-unused-parameter \
		 -Wno-declaration-after-statement

LFLAGS	 =	-Wall $(IVAR) -lpci -lX11 -lXrandr -lm

SRCDIR   = 	src
OBJDIR   = 	obj
BINDIR   = 	bin

SOURCES :=  $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/modules/*.c)
INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       =  rm -rf


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@strip $(BINDIR)/$(TARGET)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
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

check:
	cppcheck -j`nproc` --inconclusive -q --std=c99 --force --enable=warning,style,performance,portability $(SOURCES)
