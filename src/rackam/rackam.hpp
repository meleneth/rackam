#ifndef RACKAM_HPP
#define RACKAM_HPP

#include <rackam_types.hpp>

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

namespace Blackbeard {
class Rackam {
 public:
  Rackam();
  ~Rackam();

  void start_web_server(std::string base_path, int port_no);
  void main_loop();
  Newsgroup_ptr newsgroup_for_name(std::string name);

  void load_headers_from_file(Newsgroup_ptr group, std::string filename);

  WebServer_ptr webserver;
  lua_State *lua_state;
  bool still_running;
  Newsgroup_vector newsgroups;

  pthread_mutex_t self_mutex;
};

extern Blackbeard::Rackam *rackam;
}
#endif
