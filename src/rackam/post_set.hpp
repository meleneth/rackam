#ifndef POSTSET_HPP
#define POSTSET_HPP

#include <rackam_types.hpp>

namespace Blackbeard {
class PostSet {
 public:
  PostSet();
  ~PostSet();

  long long int min_message_no;
  long long int max_message_no;
  long long int size;
  int id;
  PostFile_vector postfiles;

  std::string subject;
};
}

#endif
