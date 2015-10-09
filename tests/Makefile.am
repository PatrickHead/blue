AM_CFLAGS = -O3 -I .. -I$(top_srcdir)/include -L$(top_srcdir)/src
AM_LDFLAGS =

EXTRA_DIST = 

#noinst_PROGRAMS = rt

#rt_SOURCES = rt.c
#rt_CFLAGS = ${AM_CFLAGS} ${GRAY_CFLAGS} ${XML_CFLAGS} ${CAIRO_CFLAGS}
#rt_LDADD = -lblue ${GRAY_LIBS} ${XML_LIBS} ${CAIRO_LIBS}

.PHONY: timestamps
timestamps:
	@$(top_srcdir)/tools/auto-timestamp $(top_srcdir)

all: timestamps all-am
