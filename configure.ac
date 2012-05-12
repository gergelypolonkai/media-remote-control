AC_INIT([media-remote-control], [0.1.0])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([media-remote-control], [0.1.0])

AC_PROG_CC
PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([debug], AS_HELP_STRING([--enable-debug], [Enable debugging support (default: disabled)]), [enable_debug=yes; CFLAGS="${CFLAGS} -g -Wall"], [enable_debug=no])
AM_CONDITIONAL([ENABLE_DEBUG], [test "$enable_debug" = "yes" ])
if test "$enable_debug" = "yes"; then
	AC_DEFINE([DEBUG], [1], [Define to enable debugging support])
fi

m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14], [--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

PKG_CHECK_MODULES([DBUS_GLIB], dbus-glib-1)

AC_OUTPUT([Makefile src/Makefile docs/reference/media-remote-control/Makefile])
