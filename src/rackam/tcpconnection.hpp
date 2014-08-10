#ifndef ___tcpconnection_inc
#define ___tcpconnection_inc 1

#include<string>
#include<list>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef __WIN32__
#include <winsock2.h>
#include <wininet.h>
#else
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<time.h>
#endif

#define MAXDATASIZE 960000


namespace Blackbeard {
class TCPConnection {
    public:
        // Public data members go here.
        TCPConnection(std::string hostname, int port); // Constructor
        TCPConnection(); // Constructor
        virtual ~TCPConnection(); // Destructor

        void send_data(char *buf, size_t size);
        int has_data_waiting(void);
        void send_line(std::string line);
        void slice_buffer_strings(void);
        unsigned int read_packets(void);
        unsigned int num_ticks(struct timeval *now);
        virtual void send_command(std::string command);
        void sendall(std::string cmd);
        void close_connection(void);
        unsigned int get_krate(void);
        std::string get_line(void);

        int sockfd, numbytes;  
        char buf[MAXDATASIZE];
        int buf_start_pos, buf_end_pos;
        struct hostent *he;
        struct sockaddr_in their_addr; // connector's address information 
        std::list<std::string> lines;
        int connected;
        struct timeval last_time;
        unsigned int bytes_since_last_time;
        unsigned int krate;
        time_t last_activity_at;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

}
#endif
