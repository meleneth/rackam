#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include <rackam_types.hpp>

namespace Blackbeard {
class MessageHeader {
 public:
  MessageHeader(std::shared_ptr<Newsgroup> group, long long int article_no,
                std::string msg_id, std::string subject,
                std::shared_ptr<Author> posted_by, int num_bytes);
  ~MessageHeader();

  std::shared_ptr<Newsgroup> group;
  long long int article_no;
  std::string msg_id;
  std::string subject;
  std::shared_ptr<Author> author;
  int size;

 private:
 protected:
};
}

#endif
