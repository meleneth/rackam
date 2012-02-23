#ifndef WEBREQUEST_HPP
#define WEBREQUEST_HPP

#include "tcpconnection.hpp"
#include <string>
#include <vector>

#include "post_set.hpp"
#include "post_file.hpp"
#include "newsgroup.hpp"

using std::string;
using std::vector;

class WebRequest {
    public:
        WebRequest(TCPConnection *client);
        WebRequest(string uri);
        ~WebRequest();

        void parse_uri(string uri);
        void parse_headers(void);
        void split_request_uri(string uri);
        void defaults(void);
        string get_uri(void);
        string param(string name);
        unsigned int paramn(string name);
        unsigned int param_index(string name);
        void delete_param(string name);
        void param(string name, string value);
        void param(string name, unsigned int value);

        TCPConnection *client;
        string request_string;
        string path;
        string filename;
        string content_type;
        unsigned int http_minor_version;
        unsigned int http_major_version;
        unsigned int has_cgi_params;

        vector<string> param_names;
        vector<string> param_values;

    private:
    protected:
};

#endif
