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
  still_running = 1;
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

void Rackam::main_loop()
{ 
  fd_set read_fds;
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 10;
  int fdmax = 0;
  list<TCPConnection *>::iterator c;

  //check for new incoming web request

  while(still_running) {
    FD_ZERO(&read_fds);

    FD_SET(webserver->listener->sockfd, &read_fds);
    fdmax = webserver->listener->sockfd;

    for(c = webserver->connections.begin(); c != webserver->connections.end(); ++c){
        int fd = (*c)->sockfd;
        FD_SET(fd, &read_fds);
        if(fdmax < fd){
            fdmax = fd;
        }
    }

    int result;
    do {
      result = select(fdmax+1, &read_fds, NULL, NULL, &tv);
    } while ((result == -1) && (errno == EINTR));

    if(result == -1){
        perror("select");
        exit(1);
    }

    if(FD_ISSET(webserver->listener->sockfd, &read_fds)) {
      webserver->handle_new_connection();
    }

    for(c = webserver->connections.begin(); c != webserver->connections.end(); ++c){
        if(FD_ISSET((*c)->sockfd, &read_fds)){
            (*c)->read_packets();
        }
    }

    webserver->tick();
  }
}
