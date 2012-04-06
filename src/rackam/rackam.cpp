#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<pthread.h>

#include "rackam.hpp"
#include "console.hpp"
#include "strutil.hpp"
#include "headers_parser.hpp"

using std::string;

extern "C" {
  int luaopen_Blackbeard(lua_State* L);
};

Rackam::Rackam()
{
  pthread_mutex_init(&self_mutex, NULL);
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
  std::vector<Newsgroup *>::iterator ng;
  for(ng = newsgroups.begin(); ng != newsgroups.end(); ++ng) {
    delete *ng;
  }

  lua_close(lua_state);
  if(webserver)
    delete webserver;

  pthread_mutex_destroy(&self_mutex);
}

void Rackam::start_web_server(string base_path, int port_no)
{
  webserver = new WebServer(base_path, port_no);
}

void Rackam::main_loop()
{ 
  fd_set read_fds;
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
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
      //result = select(fdmax+1, &read_fds, NULL, NULL, &tv);
      result = select(fdmax+1, &read_fds, NULL, NULL, NULL);
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

Newsgroup *Rackam::newsgroup_for_name(string name)
{
  std::vector<Newsgroup*>::iterator i;
  for(i = newsgroups.begin(); i != newsgroups.end(); ++i) {
    if((*i)->name == name) {
      return *i;
    }
  }

  Newsgroup *new_group = new Newsgroup();
  new_group->name = name;

  pthread_mutex_lock(&self_mutex);
  newsgroups.push_back(new_group);
  pthread_mutex_unlock(&self_mutex);

  return new_group;
}

void Rackam::load_headers_from_file(Newsgroup *group, string filename)
{
  int total_bytes;
  int bytes_read;

  HeadersParser *parser = new HeadersParser(group);

  char linebuffer[1024];
  std::ifstream in;
  total_bytes = 0;
  console->log("Loading full headers from " + filename);
  struct stat my_stats;
  if(stat(filename.c_str(), &my_stats) == -1){
    return;
  }
  total_bytes = my_stats.st_size;
  bytes_read = 0;

  in.open(filename.c_str(), ios::in);
  in.getline(linebuffer, 1024);
  while(!in.eof() && in){
    string line(linebuffer);
    bytes_read += line.length();
    parser->queue_line(line);
//    parser->process_line(line);

    in.getline(linebuffer, 1024);
  }
  in.close();
  parser->queue_line(""); // pthread_join
}



