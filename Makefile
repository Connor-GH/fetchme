CFLAGS=-Wall -Wpedantic -lpci -lX11 -lXrandr
CC=gcc

build:
	$(CC) $(CFLAGS) -o fetchme-easy fetchme-easy.c
clean:
	@rm -f $(DESTDIR)$(PREFIX)/bin/fetchme-easy
	


install:
	@cp -p fetchme-easy $(DESTDIR)$(PREFIX)/bin/fetchme-easy
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/fetchme-easy
