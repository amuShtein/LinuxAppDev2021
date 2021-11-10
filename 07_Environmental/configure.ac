#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Environmental project], [0.0], [xnpster@yandex.ru])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE
# Checks for libraries.
# FIXME: Replace `main' with a function in `-lrhash':

AC_CHECK_LIB([rhash], [main], [], [
    AC_MSG_ERROR([Unable to find rhash])
])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

without_readline=no
AC_ARG_WITH([readline],
            [AS_HELP_STRING([--without-readline],
              [disable support for readline])],
            [],
            [without_readline=yes])

AS_IF([test ! "x$without_readline" != xyes],
            [AC_CHECK_LIB([readline], [readline],
              [AC_SUBST([rhasher_LDADD], ["-lreadline"])
               AC_DEFINE([HAVE_LIBREADLINE], [1],
                         [Define if you have libreadline])
              ],
              [AC_MSG_FAILURE(
                 [readline test failed (--without-readline to disable)])])])

AS_IF([test "x$without_readline" != xyes],
            [AC_DEFINE([GETLINE_ENABLE], [1],
                         [Define to enable getline])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strcasecmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
