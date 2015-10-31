
AC_PREREQ(2.61)
AC_INIT([libexcept], [0.0.1], [jbboehr@gmail.com], [libexcept], 
        [https://github.com/jbboehr/libexcept])

AC_CONFIG_AUX_DIR([build])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])

AM_PROG_AR
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S

AC_HEADER_STDC

AC_EXEEXT

AM_CONDITIONAL([GCC], [test x$GCC = xyes])

PKG_CHECK_MODULES(CHECK, [check >= 0.9.12], [], [AC_MSG_FAILURE([check version too low])])
AC_CHECK_HEADERS(check.h, [], [AC_MSG_FAILURE([check.h missing])])
AC_CHECK_LIB([m], [cos], [], [AC_MSG_FAILURE([check requires libm])])
AC_CHECK_LIB([rt], [timer_create], [], [AC_MSG_WARN([check requires librt])])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])

AC_OUTPUT

