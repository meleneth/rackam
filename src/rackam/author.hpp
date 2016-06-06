#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include <rackam_types.hpp>

namespace Blackbeard {
class Author {
 public:
  Author(std::string name, Newsgroup_ptr newsgroup);
  ~Author();
  PostSet_ptr postset_for_id(int postset_id);
  PostFile_ptr postfile_for_id(int postfile_id);

  std::string name;
  long long int size;
  int id;
  int max_postset_id;
  int max_postfile_id;

  pthread_mutex_t self_mutex;

  Newsgroup_ptr newsgroup;

  MessageHeader_vector headers;
  PostSet_vector postsets;
  PostFile_vector postfiles;
  StringToPostFileMap postfiles_by_name;
};
}

#endif
