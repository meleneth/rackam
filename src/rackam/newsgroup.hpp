#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include"post_set.hpp"
#include"post_file.hpp"
#include"author.hpp"
#include"message_header.hpp"
#include"filter.hpp"

#include<string>
#include<map>
#include<vector>

class PostSet;
class PostFile;
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
    long long int size;

    Author *author_for_name(std::string authorname);
    void add_filter(std::string filter);

    std::map<void *, PostSet *> postsets;
    std::vector<PostFile *> postfiles;
    std::vector<MessageHeader *> headers;
    std::vector<Author *> authors;
    std::vector<Filter *> filters;
};

#endif
