#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include <pthread.h>

#include <rackam_types.hpp>

namespace Blackbeard {
class PostFile {
 public:
  PostFile();
  PostFile(std::string name, Author_ptr author,
           Newsgroup_ptr newsgroup);
  ~PostFile();

  std::string name;
  long long int max_message_no;
  long long int min_message_no;
  long long int size;
  int id;

  Newsgroup_ptr newsgroup;
  Author_ptr author;

  pthread_mutex_t self_mutex;
};
}

#endif
