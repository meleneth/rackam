#ifndef HEADERSPARSER_HPP
#define HEADERSPARSER_HPP

#include<rackam_types.hpp>

namespace Blackbeard {

typedef struct {
  HeadersParser * parser;
  std::vector<std::string> *headers;
} HeadersParser_thread_info_t;

void *HeadersParser_process_lines(void *s);

class HeadersParser {
  public:
    HeadersParser(std::shared_ptr<Newsgroup> newsgroup);
    ~HeadersParser();
    
    void process_line(std::string line);
    void queue_line(std::string line);

    void integrate_header(std::shared_ptr<MessageHeader> header);
    void glean_postset_info(std::shared_ptr<MessageHeader> header, std::shared_ptr<FilterMatch> match);
    void queue_header(std::shared_ptr<MessageHeader> info);

    pthread_mutex_t self_mutex;
    std::shared_ptr<Newsgroup> newsgroup;
    int running_threads;
};

}

#endif
