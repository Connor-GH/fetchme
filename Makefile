
TOPDIR 	:=  ./src
IVAR 	:=  -I. -I $(TOPDIR)/include/
PREFIX	 =  /usr/local
INSTALLBINDIR=${PREFIX}/bin


TARGET 	 =  fetchme


CC       =	gcc
WFLAGS   =  -Wall -Wpedantic -Wextra -Wno-unused-parameter 
CFLAGS	 =  -std=gnu99 -march=native -O2 -pipe $(WFLAGS) $(IVAR) 


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

# do not run cppcheck unless you are contributing.
check:
	cppcheck -j`nproc` --inconclusive -q --std=c99 --force --enable=warning,style,performance,portability $(SOURCES)
