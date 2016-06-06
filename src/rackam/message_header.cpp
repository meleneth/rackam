#include "message_header.hpp"

using namespace Blackbeard;
using namespace std;

MessageHeader::MessageHeader(Newsgroup_ptr group,
                             long long int article_no, string msg_id,
                             string subject, Author_ptr posted_by,
                             int num_bytes) {
  this->group = group;
  this->subject = subject;
  this->author = posted_by;
  this->msg_id = msg_id;
  this->article_no = article_no;
  this->size = num_bytes;
}

MessageHeader::~MessageHeader() {}
