#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include "newsgroup.hpp"
#include <string>

using std::string;

class NewsGroup;
class MessageHeader {
    public:
        MessageHeader(NewsGroup *group, unsigned long long int article_no, string msg_id, string subject, string posted_by, int num_bytes);
        ~MessageHeader();

        NewsGroup *group;
        unsigned long long int article_no;
        string msg_id;
        string subject;
        string posted_by;
        int num_bytes;
    private:
    protected:
};

#endif
