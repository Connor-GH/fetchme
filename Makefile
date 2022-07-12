
TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin


TARGET 	 =  fetchme


CC       =	gcc
CFLAGS	 =  -std=c99 -march=native -O2 -pipe $(WFLAGS) $(WNOFLAGS) $(WGCC) $(IVAR) 

WGCC   = -Wlogical-op -Wcast-align=strict
WGCC  += -fanalyzer
WGCC  += -Wsuggest-attribute=format -Wsuggest-attribute=malloc
WGCC  += -Wsuggest-attribute=pure -Wsuggest-attribute=const
WGCC  += -Wsuggest-attribute=noreturn -Wsuggest-attribute=cold

WFLAGS = -Wall -Wextra -Wpedantic \
         -Wshadow -Wvla -Wpointer-arith -Wwrite-strings -Wfloat-equal \
         -Wcast-align -Wcast-qual -Wbad-function-cast \
         -Wstrict-overflow=4 -Wunreachable-code -Wformat=2 \
         -Wundef -Wmaybe-uninitialized -Wsign-compare 
WNOFLAGS= \
		 -Wno-unused-parameter

LINKER 	 =  gcc
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

#$(TARGET):
#		cppcheck --force --enable=warning,style,performance,portability $(SOURCES)
#	    $(CC) $(CFLAGS) $(LDFLAGS) $(WFLAGS) -o $(BINDIR)/$(TARGET) $(SOURCES)
#		strip $(BINDIR)/$(TARGET)

