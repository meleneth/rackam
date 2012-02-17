bin_PROGRAMS = bin/rackam bin/rackamt

ACLOCAL_AMFLAGS = -I m4

AM_CXXFLAGS = -I src/rackam -I/usr/include/lua5.1
bin_rackam_LDADD  = -llua5.1
bin_rackamt_LDADD = -llua5.1

CLEANFILES = src/rackam/blackbeard.cxx

src/rackam/blackbeard_wrap.cxx : src/rackam/blackbeard.i src/rackam/newsgroup.hpp
	swig -c++ -lua -o src/rackam/blackbeard_wrap.cxx src/rackam/blackbeard.i

bin_rackam_SOURCES = src/rackam.cpp  \
  src/rackam/console.cpp \
  src/rackam/console.hpp \
  src/rackam/newsgroup.cpp \
  src/rackam/newsgroup.hpp \
  src/rackam/post_file.cpp \
  src/rackam/post_file.hpp \
  src/rackam/post_set.cpp \
  src/rackam/post_set.hpp \
  src/rackam/rackam.cpp \
  src/rackam/rackam.hpp \
  src/rackam/SDL_types.h \
  src/rackam/stringpattern.cpp \
  src/rackam/stringpattern.hpp \
  src/rackam/web_request.cpp \
  src/rackam/web_request.hpp \
  src/rackam/web_server.cpp \
  src/rackam/web_server.hpp \
	src/rackam/blackbeard_wrap.cxx


bin_rackamt_SOURCES = src/rackamt.cpp \
  src/rackam/console.cpp \
  src/rackam/console.hpp \
  src/rackam/newsgroup.cpp \
  src/rackam/newsgroup.hpp \
  src/rackam/post_file.cpp \
  src/rackam/post_file.hpp \
  src/rackam/post_set.cpp \
  src/rackam/post_set.hpp \
  src/rackam/rackam.cpp \
  src/rackam/rackam.hpp \
  src/rackam/SDL_types.h \
  src/rackam/stringpattern.cpp \
  src/rackam/stringpattern.hpp \
  src/rackam/web_request.cpp \
  src/rackam/web_request.hpp \
  src/rackam/web_server.cpp \
  src/rackam/web_server.hpp \
	src/rackam/blackbeard_wrap.cxx


