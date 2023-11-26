TOPDIR 	:=  ./src
IVAR 	:=  -I. -I$(TOPDIR)/include/ -I/usr/local/include

DESTDIR	=
PREFIX	= /usr
BINDIR	= $(PREFIX)/bin
DATADIR	= $(PREFIX)/share
MANDIR	= $(DATADIR)/man
MAN1DIR	= $(MANDIR)/man1

INSTALL	= install
INSTALL_DIR	= install -d
INSTALL_DATA	= install -m644
INSTALL_PROGRAM	= install
rm	= rm -rf

OBJDIR   = obj
OUTDIR   = bin

# Target and Version
TARGET 	 = fetchme
VERSION  = 1.4.9
include config_backend.mk
# These variables depend on values from config_backend.mk
INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
include cc_and_flags.mk

.PHONY: all clean remove install install-strip uninstall format pgo

all:
	$(MAKE) remove
	$(MAKE) $(TARGET)

$(TARGET): $(OBJECTS) | $(OUTDIR)
	$(CC) -o $(OUTDIR)/$@ $(F_CFLAGS) $(LFLAGS) $(INCLUDE) $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)/modules
	$(CC) -o $@ $(F_CFLAGS) $^ -c

$(PROFDIR) $(OUTDIR) $(OBJDIR)/modules:
	mkdir -p $@

clean:
	$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	$(rm) $(OUTDIR)/$(TARGET)
	@echo "Executable removed!"

install: | $(TARGET)
	$(INSTALL_DIR) $(DESTDIR)$(BINDIR)
	$(INSTALL_PROGRAM) $(OUTDIR)/$(TARGET) $(DESTDIR)$(BINDIR)
	@echo "Executable installed!"
	$(INSTALL_DIR) $(DESTDIR)$(MAN1DIR)
	$(INSTALL_DATA) docs/fetchme.1 $(DESTDIR)$(MAN1DIR)
	@echo "Man page installed!"

install-strip:
	$(MAKE) INSTALL_PROGRAM="install -s" install

uninstall:
	$(rm) $(DESTDIR)$(BINDIR)/$(TARGET)
	@echo "Exectuable removed!"
	$(rm) $(DESTDIR)$(MAN1DIR)/fetchme.1
	@echo "Man page uninstalled!"

format:
	@find . -iname *.h -o -iname *.c | xargs clang-format -style=file:.clang-format -i

pgo:
	@# only clang is supported for this PGO
	if [[ -f fetchme.profdata ]]; then \
		make CC=clang PGO=use && $(rm) fetchme.prof*; \
	else \
		make CC=clang PGO=gen CFLAGS="-DPGO_LOOP $(CFLAGS)" \
	M_TERMINAL=n M_SHELL=n && \
		LLVM_PROFILE_FILE=fetchme.profraw ./bin/fetchme > /dev/null; \
		llvm-profdata merge -output=fetchme.profdata fetchme.profraw; \
	fi
