PREFIX=/usr/local
MANDIR=/usr/share/man

all:
	cc colort.c -o colort

debug:
	cc colort.c -o colort -g

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/colort

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 colort $(DESTDIR)$(PREFIX)/bin
