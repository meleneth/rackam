#ifndef ___tcplistener_inc
#define ___tcplistener_inc 1

#include "tcpconnection.hpp"

namespace Blackbeard {
class TCPListener {
 public:
  TCPListener(int port_num);
  ~TCPListener();

  TCPConnection *get_waiting_connection();
  int has_connection_waiting();

  int port_no;
  int sockfd;                  // listen on sock_fd
  struct sockaddr_in my_addr;  // my address information
  int yes;

 private:
 protected:
};
}

#endif
