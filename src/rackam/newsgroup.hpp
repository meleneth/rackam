#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include"post_set.hpp"
#include"author.hpp"
#include"message_header.hpp"
#include"filter.hpp"

#include<string>
#include<map>
#include<vector>

class PostSet;
class MessageHeader;
class Author;
class Filter;
class Newsgroup {
  public:
    Newsgroup();
    ~Newsgroup();

    std::string name;
    long long int min_message_no;
    long long int max_message_no;

    Author *author_for_name(std::string authorname);
    void add_filter(std::string filter);

    std::map<void *, PostSet *> postsets;
    std::vector<MessageHeader *> headers;
    std::vector<Author *> authors;
    std::vector<Filter *> filters;
};

#endif
