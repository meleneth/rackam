#include "web_server.hpp"
#include "web_request.hpp"
#include "web_response.hpp"
#include "console.hpp"

#include<sstream>
using std::stringstream;

WebServer::WebServer(string web_root, int port_no)
{
    listener = new TCPListener(port_no);
    this->web_root = web_root;
}

WebServer::~WebServer()
{
    delete listener;
}

extern void handle_web_request(WebRequest *request, WebResponse *response);

void WebServer::handle_request(WebRequest *request)
{
  WebResponse response;

  console->log(request->get_uri());
  handle_web_request(request, &response);
  response.prepare_full_response();

  request->client->send_data((char *) response.full_response.c_str(), response.full_response.length());
}

void WebServer::tick(void)
{
    list <TCPConnection *>::iterator i;

    for(i = connections.begin(); i != connections.end(); ++i) {
        if((*i)->has_data_waiting()){
            WebRequest *r = new WebRequest(*i);
            handle_request(r);
            delete r;
            list <TCPConnection *>::iterator p = i;
            --i;
            connections.erase(p);
        }
    }

    list<WebDataFetcher *>::iterator h;

    for(h = handlers.begin(); h != handlers.end() ; ++h) {
        if (!(*h)->tick()) {
            list<WebDataFetcher *>::iterator j = h;
            WebDataFetcher *r = (*h);
            --h;
            delete r;
            handlers.erase(j);
        }
    }
}

void WebServer::log_to_file(string filename)
{
}

void WebServer::handle_new_connection(void)
{
    connections.push_back(listener->get_waiting_connection());
}

