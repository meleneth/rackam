#ifndef ___messageheader_inc
#define ___messageheader_inc 1

#include<rackam_types.hpp>

namespace Blackbeard {
class MessageHeader {
    public:
        MessageHeader(Newsgroup *group, long long int article_no, std::string msg_id, std::string subject, Author *posted_by, int num_bytes);
        ~MessageHeader();

        Newsgroup *group;
        long long int article_no;
        std::string msg_id;
        std::string subject;
        Author *author;
        int size;
    private:
    protected:
};
}

#endif
