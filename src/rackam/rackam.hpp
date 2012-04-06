#ifndef RACKAM_HPP
#define RACKAM_HPP

#include<string>
#include<vector>

#include<pthread.h>

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include"web_server.hpp"
#include"author.hpp"

class Rackam {
  public:
    Rackam();
    ~Rackam();

    void start_web_server(std::string base_path, int port_no);
    void main_loop();
    Newsgroup *newsgroup_for_name(std::string name);

    void load_headers_from_file(Newsgroup *group, std::string filename);

    WebServer *webserver;
    lua_State *lua_state;
    bool still_running;
    std::vector<Newsgroup *> newsgroups;

    pthread_mutex_t self_mutex;
};

extern Rackam *rackam;

#endif
