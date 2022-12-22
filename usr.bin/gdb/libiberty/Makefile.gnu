# This file was generated automatically by configure.  Do not edit.
host_alias = sun4
host_cpu = sparc
host_vendor = sun
host_os = sunos411
target_alias = sun4
target_cpu = sparc
target_vendor = sun
target_os = sunos411
target_makefile_frag = 
host_makefile_frag = 
site_makefile_frag = 
links = alloca-conf.h
VPATH = .
ALL=all.internal
#
# Makefile
#   Copyright (C) 1990, 1991, 1992 Free Software Foundation
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
#

# This file was written, and is maintained by K. Richard Pixley
# <rich@cygnus.com>.

#
# Makefile for libiberty directory
#

srcdir = .

prefix = /usr/local

exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib

datadir = $(prefix)/lib

mandir = $(prefix)/man
man1dir = $(mandir)/man1
man2dir = $(mandir)/man2
man3dir = $(mandir)/man3
man4dir = $(mandir)/man4
man5dir = $(mandir)/man5
man6dir = $(mandir)/man6
man7dir = $(mandir)/man7
man8dir = $(mandir)/man8
man9dir = $(mandir)/man9
infodir = $(prefix)/info
includedir = $(prefix)/include
oldincludedir =
docdir = $(datadir)/doc

SHELL = /bin/sh

INSTALL = install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR = ar
AR_FLAGS = qv
BISON = bison
MAKEINFO = makeinfo
RANLIB = ranlib

TARGETLIB = libiberty.a

MINUS_G = -g
CFLAGS = $(MINUS_G) -I. -I$(srcdir)/../include $(HDEFINES)

# HOST_OFILES contains the list of objects that should be in the
# library (in addition to the REQUIRED_OFILES and EXTRA_OFILES).
# A configuration may override this with a fixed list a object files
# names (hard to maintain), or some other way to generate a list.
HOST_OFILES=`cat needed-list`

# Extra targets that the top-level target depends on.
# Specifically, what needs to be made before HOST_OFILES can be used.
# Can be empty if HOST_OFILES is just a list of file names.
DO_ALSO = needed-list

# A configuration can specify extra .o files that should be included,
# even if they are in libc. (Perhaps the libc version is buggy.)
EXTRA_OFILES = 

all:	$(TARGETLIB)
.PHONY: check
check:


#### Host, target, and site specific Makefile fragments come in here.
###

# The default target just invokes make recursively.
# However, the automatic configuration (in config/mh_default).
# first causes it to figure out the objects missing in libc.
info install-info clean-info:

# NOTE: If you add new files to the library, edit 'functions.def'.
CFILES = basename.c bcmp.c bcopy.c bzero.c getopt.c getopt1.c getpagesize.c \
	getcwd.c index.c insque.c obstack.c rindex.c spaces.c \
	memcmp.c memcpy.c memmove.c memset.c strchr.c strrchr.c \
	strdup.c strerror.c strstr.c strtol.c strtoul.c vfork.c \
	vfprintf.c vprintf.c vsprintf.c sigsetmask.c concat.c fdmatch.c \
	argv.c alloca.c
# These are always included in the library.
REQUIRED_OFILES = basename.o getopt.o getopt1.o obstack.o spaces.o concat.o \
	fdmatch.o argv.o

# Do we want/need any config overrides?
#	 

STAGESTUFF = $(TARGETLIB) *.o

install: all
	$(INSTALL_DATA) $(TARGETLIB) $(libdir)/$(TARGETLIB).n
	$(RANLIB) $(libdir)/$(TARGETLIB).n
	mv -f $(libdir)/$(TARGETLIB).n $(libdir)/$(TARGETLIB)

# The default configuration adds to libiberty all those functions that are
# missing in libc.  More precisely, it includes whatever $(CC) fails to find.
# Then a sed+awk combination translates the ld error messages into
# a list of .o files.

needed-list: $(srcdir)/dummy.c $(EXTRA_OFILES) needed.awk
	$(CC) $(CFLAGS) -c $(srcdir)/dummy.c
	-($(CC) $(LDFLAGS) dummy.o $(EXTRA_OFILES) $(LOADLIBES)) >errors 2>&1 || true
	awk -f needed.awk <errors >needed-list
	-rm -f a.out errors dummy.o

# Generate an awk script that looks for functions in functions.def

needed.awk: $(srcdir)/functions.def
	echo "# !Automatically generated from $(srcdir)/functions.def"\
	  "- DO NOT EDIT!" >needed.awk
	grep '^DEF(' < $(srcdir)/functions.def \
	    | sed -e '/DEF/s|DEF.\([^,]*\).*|/\1/ { printf \" \1\.o" }|' \
	    >>needed.awk

RULE1 = $(TARGETLIB)
$(RULE1): $(REQUIRED_OFILES) $(DO_ALSO) .always.
	$(MAKE) RULE1=not-used RULE2=$(TARGETLIB) \
	     HOST_OFILES="$(HOST_OFILES)"\
	    "CC=$(CC)" "CFLAGS=$(CFLAGS)" \
	    "AR=$(AR)" "AR_FLAGS=$(AR_FLAGS)" "RANLIB=$(RANLIB)"

# Rule invoked by recursive make in $(RULE1).
RULE2 = not-used
$(RULE2): $(REQUIRED_OFILES) $(HOST_OFILES) $(EXTRA_OFILES)
	rm -rf $(TARGETLIB)
	$(AR) $(AR_FLAGS) $(TARGETLIB) \
	  $(REQUIRED_OFILES) $(HOST_OFILES) $(EXTRA_OFILES)
	$(RANLIB) $(TARGETLIB)

.always.:
# Do nothing.

.PHONEY: all etags tags ls clean stage1 stage2 .always.

etags tags: TAGS

TAGS: $(CFILES)
	etags $(HFILES) $(CFILES)

ls:
	@echo Makefile $(HFILES) $(CFILES)

# Need to deal with profiled libraries, too.

clean:
	rm -f *.a *.o core errs *~ \#* TAGS *.E a.out needed.awk errors needed-list

force:

Makefile: $(srcdir)/Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) ./config.status
