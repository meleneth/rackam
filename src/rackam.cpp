#include <iostream>

#include<rackam_types.hpp>
#include<rackam.hpp>
#include<console.hpp>
#include<newsgroup.hpp>

using namespace std;
using namespace Blackbeard;

namespace Blackbeard {
  Console *console;
  Rackam *rackam;
}

extern string newsgroup_as_json(Newsgroup *newsgroup);

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

  rackam->main_loop();

  console->log("Shutting down.");
  delete rackam;
  delete console;
  return 0;
}



