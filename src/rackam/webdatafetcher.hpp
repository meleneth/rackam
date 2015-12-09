#ifndef ___webdatafetcher_inc
#define ___webdatafetcher_inc 1

#include "web_request.hpp"
#include <string>
#include <vector>

namespace Blackbeard {
class WebDataFetcher {
 public:
  WebDataFetcher(WebRequest *request);
  virtual ~WebDataFetcher();

  virtual int tick(void);
  virtual string info_update_string(void);
  string table_id(std::string id);

  WebRequest *request;

  std::vector<string> output_lines;
  unsigned int line_no;
  unsigned int num_lines;
  std::string title;

 private:
 protected:
};
}

#endif
