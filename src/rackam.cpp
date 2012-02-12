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
  rackam = new Rackam();

  return 0;
}



