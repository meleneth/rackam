#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include<string>
#include<map>
#include<vector>
#include<pthread.h>

#include"post_set.hpp"
#include"post_file.hpp"
#include"author.hpp"
#include"message_header.hpp"
#include"filter.hpp"

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

    int max_author_id;

    Author *author_for_name(std::string authorname);
    Author *author_for_id(int author_id);
    void add_filter(std::string filter);

    std::vector<PostSet *> postsets;
    std::vector<PostFile *> postfiles;
    std::vector<MessageHeader *> headers;
    std::vector<Filter *> filters;

    std::vector<Author *> authors;
    std::map<std::string, Author *> authors_by_name;

    pthread_mutex_t self_mutex;
};

#endif
