#ifndef WEBRESPONSE_HPP
#define WEBRESPONSE_HPP

#include <string>
#include <map>

using std::string;

namespace Blackbeard {
class WebResponse {
  public:
    WebResponse();
    ~WebResponse();

    void prepare_full_response(void);
    void prepare_response_for_bytes(int num_bytes);

    string body;
    string response_line;
    string full_response;
    string content_type;

};
}

#endif
