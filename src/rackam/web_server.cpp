#include "web_server.hpp"

WebServer::WebServer(string web_root, Uint32 port_no)
{
  this->web_root = web_root;
  this->port_no = port_no;
}

WebServer::~WebServer()
{
}

void WebServer::listen()
{
}

void WebServer::tick()
{
}
