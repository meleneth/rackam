#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include "newsgroup.hpp"
#include <string>

class Newsgroup;
class MessageHeader {
    public:
        MessageHeader(Newsgroup *group, long long int article_no, std::string msg_id, std::string subject, std::string posted_by, int num_bytes);
        ~MessageHeader();

        Newsgroup *group;
        long long int article_no;
        std::string msg_id;
        std::string subject;
        std::string posted_by;
        int num_bytes;
    private:
    protected:
};

#endif
