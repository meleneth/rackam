#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <string>
#include <list>
#include "tcplistener.hpp"
#include "web_request.hpp"
#include "webdatafetcher.hpp"

using std::string;
using std::list;

// This entire webserver is such a non-standard-using
// non RFC piece of work, that this program shouldn't
// even be using it.

class WebServer {
    public:
        WebServer(string document_root, int port_no);
        ~WebServer();

        void log_to_file(string filename);
        void handle_request(WebRequest *request);
        void handle_new_connection(void);
        void register_file(string url, string filename);
        void tick(void);

        TCPListener *listener;
        list<TCPConnection *> connections;
        list<WebDataFetcher *> handlers;
        string web_root;

        std::map<string, char *> static_contents;
        std::map<string, int>    static_content_length;


    private:
    protected:
};

#endif
