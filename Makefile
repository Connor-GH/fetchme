TOPDIR 	:=  ./src
IVAR 	:=  -I. -I$(TOPDIR)/include/
PREFIX	 =  /usr
INSTALLBINDIR=${PREFIX}/bin
OBJDIR   = 	obj
BINDIR   = 	bin
rm       =  rm -rf

# Target and Version
TARGET 	 = fetchme
VERSION  = 1.4.1
include config_backend.mk
# These variables depend on values from config_backend.mk
INCLUDES:=  $(wildcard $(SRCDIR)/modules/include/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
include cc_and_flags.mk

# rebuild with `make'
$(TARGET):
	$(MAKE) remove
	@# create these directories if needed
	mkdir -p obj/modules
	mkdir -p bin/
	@# compile with multiple threads, then link.
	@echo -e "CC =\t$(CC)"
	@echo -e "LD =\t$(LINKER)"
	@echo -e "Building $(TARGET)-$(VERSION)"
	$(MAKE) $(OBJECTS)
	$(MAKE) link

link:
	$(LINKER) $(OBJECTS) $(LFLAGS) -o $(BINDIR)/$(TARGET)
	@echo "$(TARGET)-$(VERSION) built!"

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
