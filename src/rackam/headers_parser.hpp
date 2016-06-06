#ifndef HEADERSPARSER_HPP
#define HEADERSPARSER_HPP

#include <rackam_types.hpp>

namespace Blackbeard {

typedef struct {
  HeadersParser *parser;
  std::vector<std::string> *headers;
} HeadersParser_thread_info_t;

void *HeadersParser_process_lines(void *s);

class HeadersParser {
 public:
  HeadersParser(Newsgroup_ptr newsgroup);
  ~HeadersParser();

  void process_line(std::string line);
  void queue_line(std::string line);

  void integrate_header(MessageHeader_ptr header);
  void glean_postset_info(MessageHeader_ptr header,
                          FilterMatch_ptr match);
  void queue_header(MessageHeader_ptr info);

  pthread_mutex_t self_mutex;
  Newsgroup_ptr newsgroup;
  int running_threads;
};
}

#endif
