AM_CFLAGS = -O3 -I .. -I$(top_srcdir)/include -L$(top_srcdir)/src
AM_LDFLAGS =

#EXTRA_DIST = <list of file support files, scripts, etc>

#noinst_PROGRAMS = <list of test files to never include in installation>

#<test-command>_SOURCES = <test-command>.c
#<test-command>_LDADD = <ld options>

.PHONY: timestamps
timestamps:
	@$(top_srcdir)/tools/auto-timestamp $(top_srcdir)

all: timestamps all-am

clean-local:
	@(rm -f anything_that_is_created_by_tests)
