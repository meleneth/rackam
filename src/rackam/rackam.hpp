#ifndef RACKAM_HPP
#define RACKAM_HPP

#include<string>
#include<vector>

/* Include the Lua API header files. */
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include"web_server.hpp"

class Rackam {
  public:
    Rackam();
    ~Rackam();

    void start_web_server(std::string base_path, int port_no);
    void main_loop();
    Newsgroup *newsgroup_for_name(std::string name);

    void load_headers_from_file(Newsgroup *group, std::string filename);
    void load_header_line(Newsgroup *group, std::string line);

    WebServer *webserver;
    lua_State *lua_state;
    bool still_running;
    std::vector<Newsgroup *> newsgroups;
};

extern Rackam *rackam;

#endif
