#ifndef POSTSET_HPP
#define POSTSET_HPP

#include <rackam_types.hpp>

namespace Blackbeard {
class PostSet {
 public:
  PostSet();
  ~PostSet();

  message_id_t min_message_no;
  message_id_t max_message_no;
  size_in_bytes_t size;

  int id;
  PostFile_vector postfiles;

  std::string subject;
};
}

#endif
