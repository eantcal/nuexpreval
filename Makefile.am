bin_PROGRAMS = nuexpreval

nuexpreval_SOURCES = config.h main.cc

AM_CXXFLAGS = $(INTI_CFLAGS) -std=c++11 -I$(top_srcdir)/include
nuexpreval_LDADD = -lpthread $(INTI_LIBS) lib/libnuexpreval.a

SUBDIRS=lib

EXTRA_DIST=nuexpreval.sln nuexpreval.vcxproj include

