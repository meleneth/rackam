bin_PROGRAMS = bin/rackam
noinst_LIBRARIES = src/librackam.a

ACLOCAL_AMFLAGS = -I m4

AM_CXXFLAGS = -I src/rackam -I/usr/include/lua5.1 -Ivendor -lpthread -D_FILE_OFFSET_BITS=64
bin_rackam_LDADD  = -llua5.1 src/librackam.a

CLEANFILES = src/rackam/blackbeard_wrap.cxx bin/scripts/htdocs/rackam.js

src/rackam/blackbeard_wrap.cxx : src/rackam/blackbeard.i \
  src/rackam/newsgroup.hpp \
  src/rackam/post_file.hpp \
  src/rackam/post_set.hpp \
  src/rackam/post_collection.hpp \
  src/rackam/factory.hpp \
  src/rackam/rackam.hpp \
  src/rackam/filter.hpp

	swig3.0 -c++ -lua -w315 -o src/rackam/blackbeard_wrap.cxx src/rackam/blackbeard.i

RACKAM_SRC = src/rackam/author.cpp \
  src/rackam/author.hpp \
  src/rackam/console.cpp \
  src/rackam/console.hpp \
  src/rackam/controller.cpp \
  src/rackam/controller.hpp \
  src/rackam/filter.cpp \
  src/rackam/filter.hpp \
  src/rackam/headers_parser.cpp \
  src/rackam/headers_parser.hpp \
  src/rackam/message_header.cpp \
  src/rackam/message_header.hpp \
  src/rackam/newsgroup.cpp \
  src/rackam/newsgroup.hpp \
  src/rackam/post_collection.cpp \
  src/rackam/post_collection.hpp \
  src/rackam/post_file.cpp \
  src/rackam/post_file.hpp \
  src/rackam/post_set.cpp \
  src/rackam/post_set.hpp \
  src/rackam/factory.hpp \
  src/rackam/factory.cpp \
  src/rackam/rackam.cpp \
  src/rackam/rackam.hpp \
  src/rackam/SDL_types.h \
  src/rackam/stringpattern.cpp \
  src/rackam/stringpattern.hpp \
  src/rackam/strutil.cpp \
  src/rackam/strutil.hpp \
  src/rackam/tcpconnection.cpp \
  src/rackam/tcpconnection.hpp \
  src/rackam/tcplistener.cpp \
  src/rackam/tcplistener.hpp \
  src/rackam/webdatafetcher.cpp \
  src/rackam/webdatafetcher.hpp \
  src/rackam/web_request.cpp \
  src/rackam/web_request.hpp \
  src/rackam/web_response.cpp \
  src/rackam/web_response.hpp \
  src/rackam/web_server.cpp \
  src/rackam/web_server.hpp \
  src/rackam/web_static_file.cpp \
  src/rackam/web_static_file.hpp

bin_rackam_SOURCES = src/rackam.cpp src/rackam/blackbeard_wrap.cxx
src_librackam_a_SOURCES = ${RACKAM_SRC}

format-code :
	for i in ${RACKAM_SRC} src/rackam.cpp ; do clang-format-3.5 -style=Google -i $$i; done

