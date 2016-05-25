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
  long long int min_message_no;
  long long int max_message_no;
  long long int size;

  int max_author_id;

  std::shared_ptr<Author> author_for_id(int author_id);
  std::shared_ptr<Author> author_for_name(std::string author_name);
  void add_filter(std::string filter);

  std::vector<std::shared_ptr<PostSet>> postsets;
  std::vector<std::shared_ptr<PostFile>> postfiles;
  MessageHeader_vector headers;
  std::vector<std::shared_ptr<Filter>> filters;

  std::vector<std::shared_ptr<Author>> authors;
  std::map<std::string, std::shared_ptr<Author>> authors_by_name;

  pthread_mutex_t self_mutex;
};
}

#endif
