#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include<string>
using std::string;

class WebServer {
  public:
    WebServer(string web_root, int port_no);
    ~WebServer();

    void listen();
    void tick();

    string web_root;
    int port_no;
};

#endif
