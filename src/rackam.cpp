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
  console->print_logs = 1;
  console->log("Console initialized.");


  rackam = new Rackam();
  rackam->start_web_server("../htdocs", 4242);

  if(argc==2) {
    string script_name = argv[1];
    console->log("Running script " + script_name);
    if (luaL_dofile(rackam->lua_state, script_name.c_str()))
    {
      console->log(lua_tostring(rackam->lua_state, -1));
    }
  }



  console->log("Shutting down.");
  return 0;
}



