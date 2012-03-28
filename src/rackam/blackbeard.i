%module Blackbeard
%{
/* Includes the header in the wrapper code */
#include "newsgroup.hpp"
#include "post_set.hpp"
#include "post_file.hpp"
#include "web_server.hpp"
#include "web_request.hpp"
#include "web_response.hpp"
#include "stringpattern.hpp"
#include "message_header.hpp"
#include "author.hpp"
#include "filter.hpp"
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
%include "web_server.hpp"
%include "stringpattern.hpp"
%include "web_response.hpp"
%include "author.hpp"
%include "rackam.hpp"
%include "filter.hpp"
%include "message_header.hpp"

%template(NewsgroupVector) std::vector<Newsgroup *>;
%template(MessageHeaderVector) std::vector<MessageHeader *>;
%template(StringAuthorMap) std::map<string, Author *>;
%template(AuthorVector) std::vector<Author *>;
%template(FilterVector) std::vector<Filter *>;
%template(StringVector) std::vector<std::string>;

%extend Newsgroup {
  const char *get_max_message_no_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->max_message_no);
    return temp;
  }
  const char *get_min_message_no_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->min_message_no);
    return temp;
  }
}

%extend MessageHeader {
  const char *get_article_no_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->article_no);
    return temp;
  }
}

%{ 

string newsgroup_as_json(Newsgroup *newsgroup) 
{
  lua_getfield(rackam->lua_state, LUA_GLOBALSINDEX, "newsgroup_as_json");
  SWIG_Lua_NewPointerObj(rackam->lua_state, newsgroup, SWIGTYPE_p_Newsgroup, 0);
  lua_call(rackam->lua_state, 1, 1);
  
  int top;
  top = lua_gettop(rackam->lua_state);

  string result = lua_tolstring(rackam->lua_state, top, NULL);
  lua_pop(rackam->lua_state, 1);

  return result;
}

void handle_web_request(WebRequest *request, WebResponse *response)
{
  lua_getfield(rackam->lua_state, LUA_GLOBALSINDEX, "handle_web_request");
  SWIG_Lua_NewPointerObj(rackam->lua_state, request, SWIGTYPE_p_WebRequest, 0);
  SWIG_Lua_NewPointerObj(rackam->lua_state, response, SWIGTYPE_p_WebResponse, 0);
  lua_call(rackam->lua_state, 2, 0);
}

%}
