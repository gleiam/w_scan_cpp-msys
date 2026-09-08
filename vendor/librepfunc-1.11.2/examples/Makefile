#/*******************************************************************************
# * librepfunc - a collection of common functions, classes and tools.
# * See the README file for copyright information and how to reach the author.
# ******************************************************************************/














#/******************************************************************************
# * if you prefer verbose non-coloured build messages, remove the '@' here:
# *****************************************************************************/
CXX = @g++
CXXFLAGS  = -g -O3 -fPIC -Wall -Wextra -Werror=overloaded-virtual -Wfatal-errors
DEFINES   =
CPPFILES  := $(wildcard *.cpp)
EXAMPLES  = $(CPPFILES:.cpp=_example)

#/******************************************************************************
# * color definitions, RST=reset, CY=cyan, MG=magenta, BL=blue, (..)
# *****************************************************************************/
RST=\e[0m
CY=\e[1;36m
MG=\e[1;35m
BL=\e[1;34m
YE=\e[1;33m
RD=\e[1;31m
GN=\e[1;32m

#/******************************************************************************
# * programs, override if on different paths.
# *****************************************************************************/
CD              ?= cd
CP              ?= cp
CHMOD           ?= chmod
GIT             ?= git
INSTALL         ?= install
INSTALL_PROGRAM ?= $(INSTALL) -m 755
INSTALL_DATA    ?= $(INSTALL) -m 644
LN              ?= ln
LN_S            ?= $(LN) -s
LN_SF           ?= $(LN) -sf
MAKE            ?= make
MKDIR           ?= mkdir
MKDIR_P         ?= ${MKDIR} -p
PKG_CONFIG      ?= pkg-config
RM              ?= rm
SED             ?= sed
SHELL            = /bin/sh
STRIP           ?= strip
TAR             ?= tar
WGET            ?= wget


#/******************************************************************************
# * directories
# *****************************************************************************/
srcdir           = $(shell pwd)
tmpdir          ?= /tmp
prefix          ?= /usr/local
sysconfdir       = $(prefix)/etc
includedir       = $(prefix)/include
sharedstatedir   = $(prefix)/com
localstatedir    = $(prefix)/var
datarootdir      = $(prefix)/share
exec_prefix     ?= $(prefix)
bindir           = $(exec_prefix)/bin
sbindir          = $(exec_prefix)/sbin
libexecdir       = $(exec_prefix)/libexec
libdir           = $(exec_prefix)/lib
datadir          = $(datarootdir)
docdir           = $(datarootdir)/doc/$(package_name)
infodir          = $(datarootdir)/info
localedir        = $(datarootdir)/locale
mandir           = $(datarootdir)/man
man1dir          = $(mandir)/man1
man2dir          = $(mandir)/man2
man3dir          = $(mandir)/man3
man4dir          = $(mandir)/man4
man5dir          = $(mandir)/man5

SOURCES  := $(wildcard $(srcdir)/*.cpp)
#OBJS      = $(SOURCES:.cpp=.o)

LIBS      = -lrepfunc
INCLUDES  = -I./..
LDFLAGS   = -L$(srcdir)/..


%.o: %.cpp
ifeq ($(CXX),@g++)
	@echo -e "${BL} CXX $@${RST}"
endif
	$(CXX) $(CXXFLAGS) -c $(DEFINES) $(INCLUDES) -o $@ $<

%_example:
ifeq ($(CXX),@g++)
	@echo -e "${BL} CXX $@${RST}"
endif
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) $(subst _example,.cpp,$@) -o $@ $(LDFLAGS) $(LIBS)

all: librepfunc.so $(EXAMPLES)

librepfunc.so:
	$(LN_SF) ../librepfunc.so librepfunc.so


.PHONY: clean Version.h
clean:
	@$(RM) -f *_example librepfunc.so

#install: all
#	$(MKDIR_P) $(DESTDIR)$(bindir)
#	$(MKDIR_P) $(DESTDIR)$(docdir)
#	$(MKDIR_P) $(DESTDIR)$(man1dir)
#	$(INSTALL_PROGRAM) $(BINARY) $(DESTDIR)$(bindir)
#	$(INSTALL_DATA) COPYING HISTORY README $(DESTDIR)$(docdir)
#	$(INSTALL_DATA) doc/w_scan_cpp.1 $(DESTDIR)$(man1dir)
#
#uninstall:
#	$(RM) -f $(DESTDIR)$(bindir)/$(BINARY)
#	$(RM) -rf $(DESTDIR)$(docdir)
#	$(RM) -f $(DESTDIR)$(man1dir)/w_scan_cpp.1
#



#/******************************************************************************
# * debug
# *****************************************************************************/
printvars:
	@echo "VERSION            = $(VERSION)"
	@echo "LIBRARY            = $(LIBRARY)"
	@echo "CXX                = $(CXX)"
	@echo "CXXFLAGS           = $(CXXFLAGS)"
	@echo "DEFINES            = $(DEFINES)"
	@echo "INCLUDES           = $(INCLUDES)"
	@echo "SOURCES            = $(SOURCES)"
	@echo "OBJS               = $(OBJS)"
	@echo "LIBS               = $(LIBS)"
	@echo "LDFLAGS            = $(LDFLAGS)"
