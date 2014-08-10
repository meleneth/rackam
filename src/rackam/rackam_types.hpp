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


  typedef std::list<Author*> AuthorList;

  typedef std::vector<MessageHeader*> MessageHeaderVector;
  typedef std::vector<PostSet*> PostSetVector;
  typedef std::vector<PostFile*> PostFileVector;

  typedef std::map<std::string, PostFile*> StringToPostFileMap;
}

#include<pthread.h>

#endif
