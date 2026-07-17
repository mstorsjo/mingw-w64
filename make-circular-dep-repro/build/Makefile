VPATH = ..
top_srcdir = ..

all: libfoo.a

lib%.a: %.gen.def %.arm64ec.def
	cat $< $*.arm64ec.def > $@

%.gen.def: lib-common/%.def.in
	cp $< $@

%.arm64ec.def: lib-common/%.def.in
	cp $< $@

EXTRA_DIST = $(top_srcdir)/lib-common/*.def.in

DISTFILES = $(EXTRA_DIST)
distdir-am: $(DISTFILES)
