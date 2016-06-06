#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include <rackam_types.hpp>

#include <pthread.h>

namespace Blackbeard {
class Newsgroup {
 public:
  Newsgroup();
  ~Newsgroup();

  std::string name;
  message_id_t min_message_no;
  message_id_t max_message_no;
  size_in_bytes_t size;

  int max_author_id;

  Author_ptr author_for_id(int author_id);
  Author_ptr author_for_name(std::string author_name);
  void add_filter(std::string filter);

  PostSet_vector postsets;
  PostFile_vector postfiles;
  MessageHeader_vector headers;
  Filter_vector filters;
  Author_vector authors;

  std::map<std::string, Author_ptr> authors_by_name;

  pthread_mutex_t self_mutex;
};
}

#endif
