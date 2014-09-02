#ifndef RACKAMTYPES_HPP
#define RACKAMTYPES_HPP

#include<vector>
#include<map>
#include<list>
#include<string>
#include<memory>


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

  typedef std::shared_ptr<Newsgroup> NewsgroupPtr;
  typedef std::shared_ptr<Author> AuthorPtr;
  typedef std::shared_ptr<PostFile> PostFilePtr;
  typedef std::shared_ptr<WebServer> WebServerPtr;

  typedef std::list<std::shared_ptr<Author>> AuthorList;
  typedef std::list<std::shared_ptr<WebStaticFile>> WebStaticFileList;
  typedef std::list<std::shared_ptr<WebStaticFile>>::iterator WebStaticFile_list_iterator;

  typedef std::vector<std::shared_ptr<MessageHeader>> MessageHeader_vector;
  typedef std::vector<std::shared_ptr<PostSet>> PostSet_vector;
  typedef std::vector<std::shared_ptr<PostFile>> PostFile_vector;

  typedef std::map<std::string, std::shared_ptr<PostFile>> StringToPostFileMap;
}

#include<pthread.h>

#endif
