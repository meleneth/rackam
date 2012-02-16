#ifndef RACKAM_HPP
#define RACKAM_HPP

#include<string>

#include"web_server.hpp"
#include"SDL_types.h"

using std::string;

class Rackam {
  public:
    Rackam();
    ~Rackam();

    void start_web_server(string base_path, Uint32 port_no);

    WebServer *webserver;
};

extern Rackam *rackam;

#endif
