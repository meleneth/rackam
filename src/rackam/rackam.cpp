#include "rackam.hpp"

Rackam::Rackam()
{
}

Rackam::~Rackam()
{
  if(webserver)
    delete webserver;
}

void Rackam::start_web_server(string base_path, Uint32 port_no)
{
  webserver = new WebServer(base_path, port_no);
}
