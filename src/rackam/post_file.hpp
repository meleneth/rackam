#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include <pthread.h>

#include <rackam_types.hpp>
#include <post_collection.hpp>

namespace Blackbeard {
class PostFile : public PostCollection {
 public:
  PostFile();
  PostFile(std::string name, Author_ptr author,
           Newsgroup_ptr newsgroup);
  ~PostFile();

  std::string name;

  Newsgroup_ptr newsgroup;
  Author_ptr author;
  PostSet_ptr postset;

  pthread_mutex_t self_mutex;
};
}

#endif
