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
  message_id_t max_message_no;
  message_id_t min_message_no;
  size_in_bytes_t size;
  int id;

  Newsgroup_ptr newsgroup;
  Author_ptr author;
  PostSet_ptr postset;

  pthread_mutex_t self_mutex;
};
}

#endif
