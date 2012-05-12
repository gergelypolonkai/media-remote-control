#! /bin/sh

if test ! -d m4
then
	mkdir m4
fi

gtkdocize || exit 1
autoheader || exit 1
aclocal || exit 1
autoconf || exit 1
automake --add-missing --copy || exit 1
