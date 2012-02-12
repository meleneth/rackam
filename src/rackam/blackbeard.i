%module Fuego
%{
/* Includes the header in the wrapper code */
#include "entity.hpp"
#include "entitymgr.hpp"
#include "sector.hpp"
#include "console.hpp"
#include "globals.hpp"
#include "slayer.hpp"
#include "texture.hpp"
%}

/* Parse the header file to generate wrappers */
%include <std_string.i>
%include <std_map.i>
%template(StringIntMap) std::map<string, int>;
%include "entity.hpp"
%include "entitymgr.hpp"
%include "sector.hpp"
%include "console.hpp"
%include "globals.hpp"
%include "vector.hpp"
%include "slayer.hpp"
%include "texture.hpp"

