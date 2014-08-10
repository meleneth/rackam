#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include<pthread.h>

#include<rackam_types.hpp>

namespace Blackbeard {
class PostFile {
  public:
    PostFile();
    ~PostFile();

    std::string name;
    long long int max_message_no;
    long long int min_message_no;
    long long int size;
    int id;

    Newsgroup *newsgroup;
    Author *author;

    pthread_mutex_t self_mutex;
};
}

#endif
