#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include"post_set.hpp"
#include"message_header.hpp"

#include<string>
#include<map>
#include<vector>

class PostSet;
class MessageHeader;
class Newsgroup {
  public:
    Newsgroup();
    ~Newsgroup();

    string name;
    long long int min_message_no;
    long long int max_message_no;

    std::map<void *, PostSet *> postsets;
    std::vector<MessageHeader *> headers;
};

#endif
