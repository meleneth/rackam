#ifndef RACKAMTYPES_HPP
#define RACKAMTYPES_HPP

#include<vector>
#include<map>
#include<list>
#include<string>


namespace Blackbeard {
  class Console;

  class MessageHeader;
  class Newsgroup;
  class PostFile;
  class PostSet;
  class Author;
  class StringPattern;

  class Filter;
  class FilterMatch;
  class HeadersParser;

  class TCPConnection;
  class TCPListener;

  class WebServer;
  class WebRequest;
  class WebResponse;
  class WebDataFetcher;
  class WebStaticFile;


  typedef std::list<Author*> AuthorList;
  typedef std::list<WebStaticFile*> WebStaticFileList;
  typedef std::list<WebStaticFile*>::iterator WebStaticFile_list_iterator;

  typedef std::vector<MessageHeader*> MessageHeader_vector;
  typedef std::vector<PostSet*> PostSet_vector;
  typedef std::vector<PostFile*> PostFile_vector;

  typedef std::map<std::string, PostFile*> StringToPostFileMap;
}

#include<pthread.h>

#endif
