#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include <rackam_types.hpp>

namespace Blackbeard {
class MessageHeader {
 public:
  MessageHeader(Newsgroup_ptr group, long long int article_no,
                std::string msg_id, std::string subject,
                Author_ptr posted_by, int num_bytes);
  ~MessageHeader();

  Newsgroup_ptr group;
  long long int article_no;
  std::string msg_id;
  std::string subject;
  Author_ptr author;
  int size;

 private:
 protected:
};
}

#endif
