%module Blackbeard
%{
/* Includes the header in the wrapper code */
#include "newsgroup.hpp"
#include "post_set.hpp"
#include "post_file.hpp"
#include "web_request.hpp"
#include "stringpattern.hpp"
#include "rackam.hpp"

#include <string>

using std::string;
%}

/* Parse the header file to generate wrappers */
%include <std_string.i>
%include <std_map.i>
%include <std_vector.i>
/*%template(StringIntMap) std::map<string, int>; */

%include "newsgroup.hpp"
%include "post_set.hpp"
%include "post_file.hpp"
%include "web_request.hpp"
%include "stringpattern.hpp"


%{ 

string newsgroup_as_json(Newsgroup *newsgroup) 
{
  printf("Lua TOP: %d\n", lua_gettop(rackam->lua_state));
  lua_getfield(rackam->lua_state, LUA_GLOBALSINDEX, "newsgroup_as_json");
  SWIG_Lua_NewPointerObj(rackam->lua_state, newsgroup, SWIGTYPE_p_Newsgroup, 0);
  printf("Lua TOP: %d\n", lua_gettop(rackam->lua_state));
  lua_call(rackam->lua_state, 1, 1);
  printf("Lua TOP: %d\n", lua_gettop(rackam->lua_state));
  
  int top;
  top = lua_gettop(rackam->lua_state);
  size_t length;

  string result = lua_tolstring(rackam->lua_state, top, NULL);
  lua_pop(rackam->lua_state, 1);
  printf("Lua TOP: %d\n", lua_gettop(rackam->lua_state));

  return result;
}

%}
