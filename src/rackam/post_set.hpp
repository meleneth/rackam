#ifndef POSTSET_HPP
#define POSTSET_HPP

#include <rackam_types.hpp>
#include <post_collection.hpp>

namespace Blackbeard {
class PostSet : public PostCollection {
 public:
  PostSet();
  ~PostSet();

  PostFile_vector postfiles;

  std::string subject;
};
}

#endif
