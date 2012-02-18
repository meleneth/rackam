#include "rackam.hpp"
#include "console.hpp"

extern "C" {
  int luaopen_Blackbeard(lua_State* L);
};

Rackam::Rackam()
{
  lua_state = lua_open();
  luaopen_base(lua_state);
  luaopen_table(lua_state);
  luaopen_string(lua_state);
  luaopen_math(lua_state);
  luaopen_Blackbeard(lua_state);

  console->log("Lua initialized.");
}

Rackam::~Rackam()
{
  if(webserver)
    delete webserver;
}

void Rackam::start_web_server(string base_path, int port_no)
{
  webserver = new WebServer(base_path, port_no);
}
