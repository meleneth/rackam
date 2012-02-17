#include <iostream>

#include <rackam.hpp>
#include <console.hpp>

using namespace std;

Console *console;
Rackam *rackam;


int main(int argc, char *argv[])
{
  cout << "rackam: rackam\n";

  console = new Console();
  console->log("Console initialized.");


  rackam = new Rackam();
  rackam->start_web_server("../htdocs", 4242);

  console->log("Shutting down.");
  return 0;
}



