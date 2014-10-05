AM_CFLAGS = -O3 -I .. -I $(top_srcdir)/include
AM_LDFLAGS =

#lib_LTLIBRARIES = <mylib.la>

#LDADD = <mylib.la>

#<mylib>_la_SOURCES = <mysourcelist>
#<mylib>_la_LDFLAGS = -version-info 0:1:0
#<mylib>_la_CFLAGS = ${AM_CFLAGS}

.PHONY: timestamps
timestamps:
	@$(top_srcdir)/tools/auto-timestamp $(top_srcdir)

all: timestamps all-am
