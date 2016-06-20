#ifndef POSTCOLLECTION_HPP
#define POSTCOLLECTION_HPP

#include <rackam_types.hpp>

namespace Blackbeard {
class PostCollection {
  public:
    PostCollection();
    ~PostCollection();

  message_id_t min_message_no;
  message_id_t max_message_no;
  int id;

  size_in_bytes_t size;
};
}

#endif
