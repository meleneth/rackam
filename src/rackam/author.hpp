#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include<vector>
#include<string>

#include<pthread.h>

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
    PostSet   *postset_for_id(int postset_id);
    PostFile *postfile_for_id(int postfile_id);

    std::string name;
    long long int size;
    int id;
    int max_postset_id;
    int max_postfile_id;

    pthread_mutex_t self_mutex;

    Newsgroup *newsgroup;

    std::vector<MessageHeader *> headers;
    std::vector<PostSet *> postsets;
    std::vector<PostFile *> postfiles;
    std::map<std::string, PostFile *> postfiles_by_name;
};

#endif
