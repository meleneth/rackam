#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include<vector>
#include<string>

#include"message_header.hpp"
#include"newsgroup.hpp"
#include"post_file.hpp"
#include"post_set.hpp"

class MessageHeader;
class Newsgroup;
class PostFile;
class PostSet;
class Author {
  public:
    Author(std::string name);
    ~Author();

    std::string name;
    long long int size;
    Newsgroup *newsgroup;

    std::vector<MessageHeader *> headers;
    std::vector<PostSet *> postsets;
    std::vector<PostFile *> postfiles;
};

#endif
