#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<pthread.h>

#include "rackam.hpp"
#include "console.hpp"
#include "strutil.hpp"

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
  running_threads = 0;
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
  queue_header(NULL); // pthread_join
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
    //integrate_header(info);
    queue_header(info);
}

void Rackam::queue_header(MessageHeader *info)
{
  static std::vector<MessageHeader *> *headers = NULL;
  static std::vector<pthread_t> threads;
  pthread_t new_thread;
  
  if(!headers){
    headers = new std::vector<MessageHeader *>;
  }

  if(!info){
    // Special argument!  info == NULL, flush our headers, wait for threads to finish
    // well, it USED to wait for threads to finish... 
    // now it does it by looking for running_threads to hit 0
    if(headers){
      pthread_mutex_lock(&self_mutex);
      running_threads++;
      pthread_mutex_unlock(&self_mutex);

      pthread_create(&new_thread, NULL, Rackam_integrate_headers, (void *)headers);
      pthread_detach(new_thread);
    }

    if(running_threads) {
      pthread_mutex_lock(&self_mutex);
    }
    while(running_threads) {
      pthread_mutex_unlock(&self_mutex);
      sched_yield();
      pthread_mutex_lock(&self_mutex);
    }
    return;
  }

  headers->push_back(info);
  if(headers->size() > 50) {
    pthread_create(&new_thread, NULL, Rackam_integrate_headers, (void *) headers);
    pthread_detach(new_thread);
    threads.push_back(new_thread);

    pthread_mutex_lock(&self_mutex);
    running_threads++;
    pthread_mutex_unlock(&self_mutex);

    // Spawn thread, save it in our list for later, empty out headers
    headers = NULL;
  }
  
}

void *Rackam_integrate_headers(void *h)
{
  std::vector<MessageHeader *> *headers = (std::vector<MessageHeader *> *) h;
  std::vector<MessageHeader *>::iterator i;
  for(i = headers->begin(); i != headers->end(); ++i){
    rackam->integrate_header(*i);
  }
  headers->empty();
  delete headers;
  pthread_mutex_lock(&rackam->self_mutex);
  rackam->running_threads--;
  pthread_mutex_unlock(&rackam->self_mutex);
}

void Rackam::integrate_header(MessageHeader *header)
{
    std::vector<Filter *>::iterator f;
    for(f = header->group->filters.begin(); f != header->group->filters.end(); ++f){
      FilterMatch *match = (*f)->match(header->subject);
        if(match){
            if( (match->postset_num_files!=0) 
                 && (match->postfile_num_pieces !=0)
                 && (match->postfile_filename.length() != 0) ) {
              glean_postset_info(header, match);
              delete match;
              return;
            }
        }
    }
  
    pthread_mutex_lock(&header->group->self_mutex);
    header->group->headers.push_back(header);
    pthread_mutex_unlock(&header->group->self_mutex);

    pthread_mutex_lock(&header->author->self_mutex);
    header->author->headers.push_back(header);
    header->author->size += header->size;
    pthread_mutex_unlock(&header->author->self_mutex);
}

void Rackam::glean_postset_info(MessageHeader *header, FilterMatch *match)
{
  // Start at the beginning.  Just make PostFile, don't even need to actually
  // keep the message id's yet

  // This will all run through the database somehow soon, don't worry about it.

  //Don't worry about it he says, do you even KNOW what that did to threading...
 
  PostFile *file = get_postfile_for_filename(header->author, match->postfile_filename);

  // omg denormalized someone shoot me
  pthread_mutex_lock(&file->self_mutex);
  file->size += header->size;
  pthread_mutex_unlock(&file->self_mutex);

  pthread_mutex_lock(&header->author->self_mutex);
  header->author->size += header->size;
  pthread_mutex_unlock(&header->author->self_mutex);

  pthread_mutex_lock(&header->author->newsgroup->self_mutex);
  header->author->newsgroup->size += header->size;
  pthread_mutex_unlock(&header->author->newsgroup->self_mutex);

  delete header;
}

PostFile *Rackam::get_postfile_for_filename(Author *author, std::string filename)
{
  // SHIP IT
  // uh I mean naive implementation here re-write plz
  std::map<std::string, PostFile *>::iterator result;

  pthread_mutex_lock(&author->self_mutex); // is this one needed?
  result = author->postfiles_by_name.find(filename);
  if(result != author->postfiles_by_name.end()) {
    pthread_mutex_unlock(&author->self_mutex);
    return result->second;
  }
  pthread_mutex_unlock(&author->self_mutex);

  PostFile *new_file = new PostFile();
  new_file->name = filename;
  new_file->author = author;

  pthread_mutex_lock(&author->self_mutex);
  author->max_postfile_id++;
  new_file->id = author->max_postfile_id;
  author->postfiles.push_back(new_file);
  author->postfiles_by_name[filename] = new_file;
  pthread_mutex_unlock(&author->self_mutex);

  pthread_mutex_lock(&author->newsgroup->self_mutex);
  author->newsgroup->postfiles.push_back(new_file);
  pthread_mutex_unlock(&author->newsgroup->self_mutex);

  return new_file;
}


