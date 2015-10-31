
check_PROGRAMS = test

test_SOURCES = test.c

TESTS = test

AM_CPPFLAGS = -I$(top_builddir)/src -I$(top_srcdir)/src
AM_LDFLAGS = -static  # for speed and Valgrind
AM_CFLAGS = -pthread
LDADD = $(top_builddir)/src/libexcept.la -lcheck

