VERSION := $(shell cat VERSION)
MAJOR   := $(firstword $(subst ., ,$(VERSION)))

CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra
PREFIX  ?= /usr/local
LIBDIR  ?= $(PREFIX)/lib
INCDIR  ?= $(PREFIX)/include

LIB     := libblockfont.so
SONAME  := $(LIB).$(MAJOR)
REAL    := $(LIB).$(VERSION)

EXAMPLES := example/character_map example/repo_name

.PHONY: all examples install uninstall clean

all: $(LIB)

$(REAL): blockfont.c blockfont.h VERSION
	$(CC) $(CFLAGS) -fPIC -shared -Wl,-soname,$(SONAME) -o $@ blockfont.c

$(SONAME): $(REAL)
	ln -sf $(REAL) $@

$(LIB): $(SONAME)
	ln -sf $(SONAME) $@

examples: $(EXAMPLES)

example/%: example/%.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L. -lblockfont -Wl,-rpath,'$$ORIGIN/..'

install: $(LIB)
	install -Dm755 $(REAL) $(DESTDIR)$(LIBDIR)/$(REAL)
	ln -sf $(REAL) $(DESTDIR)$(LIBDIR)/$(SONAME)
	ln -sf $(SONAME) $(DESTDIR)$(LIBDIR)/$(LIB)
	install -Dm644 blockfont.h $(DESTDIR)$(INCDIR)/blockfont.h

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(REAL) $(DESTDIR)$(LIBDIR)/$(SONAME) \
	      $(DESTDIR)$(LIBDIR)/$(LIB) $(DESTDIR)$(INCDIR)/blockfont.h

clean:
	rm -f $(LIB) $(SONAME) $(REAL) $(EXAMPLES)
