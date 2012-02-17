#include <iostream>

#include<console.hpp>
#include<rackam.hpp>
using namespace std;

Console *console;
Rackam *rackam;

int main(int argc, char *argv[])
{
  cout << "rackam: rackamt\n";
  console = new Console();
  console->log("Console initialized.");

  return 0;
}



