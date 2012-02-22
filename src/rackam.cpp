#include <iostream>

#include <rackam.hpp>
#include <console.hpp>
#include<newsgroup.hpp>

using namespace std;

Console *console;
Rackam *rackam;

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


  Newsgroup *f;
  f = new Newsgroup();
  f->name = "alt.binaries.erotica.divx";
  f->max_message_no = 3456789;
  f->min_message_no = 4294967297;

  // Now for something /really/ amazing
  /*int top;
  top = lua_gettop(rackam->lua_state);
  SWIG_Lua_NewPointerObj(rackam->lua_state, f, SWIGTYPE_p_Newsgroup, 0);
  lua_pushstring(rackam->lua_state, "newsgroup_as_json");
  lua_settop(rackam->lua_state, top);
*/

/*  lua_getfield(rackam->lua_state, LUA_GLOBALSINDEX, "newsgroup_as_json");
  SWIG_Lua_NewPointerObj(rackam->lua_state, f, swig_types[0], 0);
  lua_call(rackam->lua_state, 1, 1);
*/
  /* this is a dead end, even tho the code is close to correct.  This code must be embedded in the wrapper
     in order to function, so I'm going to rewrite it in the .i file tomorrow.

     sucks to have a extra C++ function to handle "call newsgroup_as_json on this object", but that's not 
     really what I'm going to be doing anyways - I'm going to be handling a web request, so the one special
     case function is going to be my golden doorway to fabulous riches.  Sigh.  Hopefully it works tomorrow
     I really want this to work.  Holy Grail anyone? ... hopefully not moby dick :/

     */

  string result = newsgroup_as_json(f);
  printf("C++ Result: %s", result.c_str());

  console->log("Shutting down.");
  return 0;
}



