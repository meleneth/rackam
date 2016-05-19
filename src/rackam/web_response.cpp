#include "web_response.hpp"
#include "console.hpp"

#include <sstream>

using std::stringstream;
using namespace Blackbeard;

WebResponse::WebResponse() { content_type = "text/html"; }

WebResponse::~WebResponse() {}

void WebResponse::prepare_full_response() {
  stringstream s;

  s << "HTTP/1.1 200 OK\r\n";
  s << "Content-length: " << body.length() << "\r\n";
  s << "Content-type: " << content_type << "; charset=UTF-8\r\n";
  s << "Access-Control-Allow-Origin: http://rinzler:3000\r\n";
  s << "Connection: close\r\n";
  s << "\r\n";
  s << body;

  full_response = s.str();
}

void WebResponse::prepare_response_for_bytes(int num_bytes) {
  // This is used when returning a file
  stringstream s;

  s << "HTTP/1.1 200 OK\r\n";
  s << "Content-length: " << num_bytes << "\r\n";
  s << "Content-type: " << content_type << "\r\n";
  s << "Access-Control-Allow-Origin: http://rinzler:3000\r\n";
  s << "Connection: close\r\n";
  s << "\r\n";

  full_response = s.str();
}
