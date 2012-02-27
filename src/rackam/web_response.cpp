#include "web_response.hpp"

#include<sstream>

using std::stringstream;

WebResponse::WebResponse()
{
}

WebResponse::~WebResponse()
{
}

void WebResponse::prepare_full_response()
{
  stringstream s;

  s << "HTTP 1.1 200 OK\r\n";
  s << "Content-length: " << body.length() << "\r\n";
  s << "Connection: close\r\n";
  s << "\r\n";
  s << body;

  full_response = s.str();

}
