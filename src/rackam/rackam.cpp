#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "rackam.hpp"
#include "console.hpp"
#include "strutil.hpp"

using std::string;

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
  newsgroups.push_back(new_group);
  return new_group;
}

void Rackam::load_headers_from_file(Newsgroup *group, string filename)
{
  int total_bytes;
  int bytes_read;

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
    load_header_line(group, line);

    in.getline(linebuffer, 1024);
  }
  in.close();
}

void Rackam::load_header_line(Newsgroup *group, string line)
{
    vector<string> header_pieces;
    // scrub upper ASCII out of xover_line
    unsigned int i;

    // Upper ASCII gets discarded, don't parse the message at all (segfaults)
    for(i = 0; i < line.length(); i++) {
      char c = line[i];
      //        console->log(s.str());
      if (c < 0){
        return;
       printf("Error.  Load of headers failed.  Check it out.\n");
        return;
      }
    }

    Tokenize(line, header_pieces, "\t");

    if(header_pieces.size() < 8 ) return;
    if(header_pieces.size() > 9 ) return;

    std::string msg_id = header_pieces[4];
    msg_id = msg_id.substr(1, msg_id.length() - 2);
    std::string subject = header_pieces[1];
    Author *posted_by = group->author_for_name(header_pieces[2]);

    MessageHeader *info = new MessageHeader(group, 
      atoll(header_pieces[0].c_str()), 
      msg_id, 
      subject, 
      posted_by, 
      atoi(header_pieces[5].c_str())
    );
    //26487885        Masters of the Universe DVD Set: Disk 8 [40/83] yEnc - "MOTU_Disk8.part38.rar" (101/114)        anonxyz29@hotmail.com (Ragnarock)       Sat, 18 Mar 2006 05:29:36 -0600    <-o2dnev5dJm9cobZRVn-sg@giganews.com>           456758  3508    Xref: number1.nntp.dca.giganews.com alt.binaries.multimedia.cartoons:26487885

    group->headers.push_back(info);
    posted_by->headers.push_back(info);
}
