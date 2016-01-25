prefix=/usr/local

all:
	cc colort.c -o colort

debug:
	cc colort.c -o colort -g

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/colort

install:
	mkdir -p $(DESTDIR)$(prefix)/bin
	install -m 0755 colort $(DESTDIR)$(prefix)/bin
