#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include<string>
#include"SDL_types.h"
using std::string;

#include"newsgroup.hpp"

class PostFile {
  public:
    PostFile();
    ~PostFile();

    string name;
    Uint64 max_message_no;
    Uint64 min_message_no;

    Newsgroup *newsgroup;
};

#endif
