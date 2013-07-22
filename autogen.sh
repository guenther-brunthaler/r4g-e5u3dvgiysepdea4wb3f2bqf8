#! /bin/sh
# This script can be run with ./configure arguments or without any arguments.
#
# (c) 2013 by Guenther Brunthaler <gb_about_gnu@gmx.net>.
#
# This script is free software.
# Distribution is permitted under the terms of the LGPLv3.


die() {
	echo "ERROR: $*" >& 2
	false; exit
}


run() {
	"$@" && return
	die "Command >>>$*<<< failed with return code ${?}!"
}


have_exe() {
	which -- "$1" > /dev/null 2>& 1
}


test -f autogen.sh || die "Must be called from top-level source directory!"
# Check whether version control tool is available.
HAVE_BZR=; test -d .bzr && have_exe bzr && HAVE_BZR=Y
# Options used internally by Makefile_am.in.
test -n "$HAVE_BZR" && test -f current_version.txt \
	&& run rm current_version.txt
run make -f Makefile_am.in top_srcdir=. \
	Makefile.am configure.ac NEWS ChangeLog
run autoreconf -i
exec ./configure "$@"
