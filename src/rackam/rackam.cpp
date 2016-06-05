#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

#include "rackam_types.hpp"

#include "rackam.hpp"
#include "console.hpp"
#include "strutil.hpp"
#include "headers_parser.hpp"
#include "web_server.hpp"
#include "newsgroup.hpp"
#include "tcpconnection.hpp"
#include "tcplistener.hpp"

using namespace Blackbeard;
using namespace std;

extern "C" { int luaopen_Blackbeard(lua_State* L); };

Rackam::Rackam() {
  pthread_mutex_init(&self_mutex, NULL);
  lua_state = lua_open();
  luaL_openlibs(lua_state);
  luaopen_Blackbeard(lua_state);
  webserver = nullptr;

  console->log("Lua initialized.");
  still_running = 1;
}

Rackam::~Rackam() {
  newsgroups.empty();

  lua_close(lua_state);
  webserver = nullptr;

  pthread_mutex_destroy(&self_mutex);
}

void Rackam::start_web_server(string base_path, int port_no) {
  webserver = make_shared<WebServer>(base_path, port_no);
}

void Rackam::main_loop() {
  fd_set read_fds;
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  int fdmax = 0;

  // check for new incoming web request

  while (still_running) {
    FD_ZERO(&read_fds);

    FD_SET(webserver->listener->sockfd, &read_fds);
    fdmax = webserver->listener->sockfd;

    for (auto connection : webserver->connections) {
      int fd = connection->sockfd;
      FD_SET(fd, &read_fds);
      if (fdmax < fd) {
        fdmax = fd;
      }
    }

    int result;
    do {
      // result = select(fdmax+1, &read_fds, NULL, NULL, &tv);
      result = select(fdmax + 1, &read_fds, NULL, NULL, NULL);
    } while ((result == -1) && (errno == EINTR));

    if (result == -1) {
      perror("select");
      exit(1);
    }

    if (FD_ISSET(webserver->listener->sockfd, &read_fds)) {
      webserver->handle_new_connection();
    }

    for (auto connection : webserver->connections) {
      if (FD_ISSET(connection->sockfd, &read_fds)) {
        connection->read_packets();
      }
    }

    webserver->tick();
  }
}

Newsgroup_ptr Rackam::newsgroup_for_name(string name) {
  for (auto newsgroup : newsgroups) {
    if (newsgroup->name.compare(name) == 0) {
      return newsgroup;
    }
  }

  auto new_group = make_shared<Newsgroup>();
  new_group->name = name;

  pthread_mutex_lock(&self_mutex);
  newsgroups.push_back(new_group);
  pthread_mutex_unlock(&self_mutex);

  return new_group;
}

void Rackam::load_headers_from_file(Newsgroup_ptr group, string filename) {
  int total_bytes;
  int bytes_read;

  HeadersParser parser(group);

  char linebuffer[1024];
  std::ifstream in;
  total_bytes = 0;
  console->log("Loading full headers from " + filename);
  struct stat my_stats;
  if (stat(filename.c_str(), &my_stats) == -1) {
    return;
  }
  total_bytes = my_stats.st_size;
  bytes_read = 0;

  in.open(filename.c_str(), ios::in);
  in.getline(linebuffer, 1024);
  while (!in.eof() && in) {
    string line(linebuffer);
    bytes_read += line.length();
    parser.queue_line(line);
    //    parser->process_line(line);

    in.getline(linebuffer, 1024);
  }
  in.close();
  parser.queue_line("");  // pthread_join
}
