#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include<string>
using std::string;

#include"SDL_types.h"

class WebServer {
  public:
    WebServer(string web_root, Uint32 port_no);
    ~WebServer();

    void listen();
    void tick();

    string web_root;
    Uint32 port_no;
};

#endif
