#ifndef RACKAM_HPP
#define RACKAM_HPP

class Rackam {
  public:
    Rackam();
    ~Rackam();

    void start_web_server(string base_path, Uint32 port_no);

    WebServer *webserver;
};

extern Rackam *rackam;

#endif
