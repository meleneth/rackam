%module Blackbeard
%{
/* Includes the header in the wrapper code */
#include "rackam_types.hpp"
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
#include "web_static_file.hpp"

#include <string>

using std::string;
using namespace Blackbeard;
%}

/* Parse the header file to generate wrappers */
%include <std_string.i>
%include <std_map.i>
%include <std_vector.i>
%import "shared_ptr.i"
/*%template(StringIntMap) std::map<string, int>; */

%template(NewsgroupPtr) std::shared_ptr<Blackbeard::Newsgroup>;
%template(PostFilePtr) std::shared_ptr<Blackbeard::PostFile>;
%template(AuthorPtr) std::shared_ptr<Blackbeard::Author>;
%template(WebServerPtr) std::shared_ptr<Blackbeard::WebServer>;
%template(MessageHeaderPtr) std::shared_ptr<Blackbeard::MessageHeader>;
%template(WebStaticFilePtr) std::shared_ptr<Blackbeard::WebStaticFile>;

%include "rackam_types.hpp"
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
%include "web_static_file.hpp"

%template(Newsgroup_vector) std::vector<std::shared_ptr<Blackbeard::Newsgroup>>;
%template(MessageHeader_vector) std::vector<std::shared_ptr<Blackbeard::MessageHeader>>;
%template(StringAuthor_map) std::map<string, std::shared_ptr<Blackbeard::Author>>;
%template(Author_vector) std::vector<std::shared_ptr<Blackbeard::Author>>;
%template(Filter_vector) std::vector<std::shared_ptr<Blackbeard::Filter>>;
%template(String_vector) std::vector<std::string>;
%template(PostSet_vector) std::vector<std::shared_ptr<Blackbeard::PostSet>>;
%template(PostFile_vector) std::vector<std::shared_ptr<Blackbeard::PostFile>>;

%extend Blackbeard::Newsgroup {
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
  const char *get_size_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->size);
    return temp;
  }
}

%extend Blackbeard::PostSet {
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
  const char *get_size_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->size);
    return temp;
  }
}

%extend Blackbeard::PostFile {
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
  const char *get_size_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->size);
    return temp;
  }
}

%extend Blackbeard::MessageHeader {
  const char *get_article_no_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->article_no);
    return temp;
  }
  const char *get_size_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->size);
    return temp;
  }
}

%extend Blackbeard::Author {
  const char *get_size_str()
  { 
    static char temp[1024];
    sprintf(temp, "%llu", $self->size);
    return temp;
  }
}

%extend Blackbeard::Filter {
  const char *get_num_matched_str()
  {
    static char temp[1024];
    sprintf(temp, "%llu", $self->num_matched);
    return temp;
  }
}

%{ 

namespace Blackbeard {
string newsgroup_as_json(Newsgroup *newsgroup) 
{
  lua_getfield(rackam->lua_state, LUA_GLOBALSINDEX, "newsgroup_as_json");
  SWIG_Lua_NewPointerObj(rackam->lua_state, newsgroup, SWIGTYPE_p_Blackbeard__Newsgroup, 0);
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
  SWIG_Lua_NewPointerObj(rackam->lua_state, request, SWIGTYPE_p_Blackbeard__WebRequest, 0);
  SWIG_Lua_NewPointerObj(rackam->lua_state, response, SWIGTYPE_p_Blackbeard__WebResponse, 0);
  lua_call(rackam->lua_state, 2, 0);
}

}

%}
