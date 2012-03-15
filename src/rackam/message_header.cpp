#include "message_header.hpp"

using std::string;

MessageHeader::MessageHeader(Newsgroup *group, long long int article_no, string msg_id, string subject, string posted_by, int num_bytes)
{
    this->group = group;
    this->subject = subject;
    this->posted_by = posted_by;
    this->msg_id = msg_id;
    this->article_no = article_no;
    this->num_bytes = num_bytes;
}

MessageHeader::~MessageHeader()
{
}

