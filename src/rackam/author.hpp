#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include<vector>
#include<string>

#include"message_header.hpp"
#include"newsgroup.hpp"

class MessageHeader;
class Newsgroup;
class Author {
  public:
    Author(std::string name);
    ~Author();

  std::string name;
  std::vector<MessageHeader *> headers;
  Newsgroup *newsgroup;
};

#endif
