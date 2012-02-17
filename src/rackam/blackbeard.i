%module Blackbeard
%{
/* Includes the header in the wrapper code */
#include "newsgroup.hpp"
#include "post_set.hpp"
#include "post_file.hpp"
#include "web_request.hpp"
#include "stringpattern.hpp"
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
