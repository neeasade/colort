prefix=/usr/local

all:
	cc colort.c -o colort

debug:
	cc colort.c -o colort -g

uninstall: colort
	rm -f $(DESTDIR)$(prefix)/bin/colort

install: colort
	install -m 0755 colort $(DESTDIR)$(prefix)/bin
