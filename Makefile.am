
SUBDIRS = src . tests

ACLOCAL_AMFLAGS = -I m4 --install

# These flags are gcc specific
if GCC
export AM_CFLAGS = -Wall -Wextra -Wdeclaration-after-statement  \
		-Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
endif

