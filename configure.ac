#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(cstune, gamma, jonas.gehring@boolsoft.org)
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([src/player.cpp])
AC_CONFIG_HEADER([config.h])

sinclude(build/readline.m4)
sinclude(build/xine.m4)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
VL_LIB_READLINE()
if test "$vl_c_lib_readline" = "no"; then
	AC_MSG_ERROR([Error - Can't compile without readline])
fi
if test "$vl_c_lib_readline_history" = "no"; then
	AC_MSG_ERROR([Error - Can't compile without readline])
fi
AM_PATH_XINE([1.1.0], ,AC_MSG_ERROR([Error - xine was not found]))

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_STAT
AC_CHECK_FUNCS([regcomp strchr])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
