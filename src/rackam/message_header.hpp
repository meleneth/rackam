#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include <rackam_types.hpp>

namespace Blackbeard {
class MessageHeader {
 public:
  MessageHeader(Newsgroup_ptr group, message_id_t article_no,
                std::string msg_id, std::string subject,
                Author_ptr posted_by, size_in_bytes_t num_bytes);
  ~MessageHeader();

  Newsgroup_ptr group;
  message_id_t article_no;
  std::string msg_id;
  std::string subject;
  Author_ptr author;
  size_in_bytes_t size;

 private:
 protected:
};
}

#endif
