#ifndef RACKAM_HPP
#define RACKAM_HPP

#include<string>

/* Include the Lua API header files. */
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include"web_server.hpp"

using std::string;

class Rackam {
  public:
    Rackam();
    ~Rackam();

    void start_web_server(string base_path, int port_no);
    void main_loop();

    WebServer *webserver;
    lua_State *lua_state;
    bool still_running;
};

extern Rackam *rackam;

#endif
