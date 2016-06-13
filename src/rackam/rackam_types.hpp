#ifndef RACKAMTYPES_HPP
#define RACKAMTYPES_HPP

#include<vector>
#include<map>
#include<list>
#include<string>
#include<memory>


namespace Blackbeard {

  typedef int64_t size_in_bytes_t;
  typedef int64_t message_id_t;

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

  typedef std::shared_ptr<Author> Author_ptr;
  typedef std::shared_ptr<Filter> Filter_ptr;
  typedef std::shared_ptr<FilterMatch> FilterMatch_ptr;
  typedef std::shared_ptr<MessageHeader> MessageHeader_ptr;
  typedef std::shared_ptr<Newsgroup> Newsgroup_ptr;
  typedef std::shared_ptr<PostFile> PostFile_ptr;
  typedef std::shared_ptr<PostSet> PostSet_ptr;
  typedef std::shared_ptr<WebServer> WebServer_ptr;
  typedef std::shared_ptr<WebStaticFile> WebStaticFile_ptr;

  typedef std::list<Author_ptr> AuthorList;
  typedef std::list<WebStaticFile_ptr> WebStaticFileList;

  typedef std::vector<Author_ptr> Author_vector;
  typedef std::vector<Filter_ptr> Filter_vector;
  typedef std::vector<MessageHeader_ptr> MessageHeader_vector;
  typedef std::vector<Newsgroup_ptr> Newsgroup_vector;
  typedef std::vector<PostFile_ptr> PostFile_vector;
  typedef std::vector<PostSet_ptr> PostSet_vector;

  typedef std::map<std::string, PostFile_ptr> StringToPostFileMap;
}

#include<pthread.h>

#endif
