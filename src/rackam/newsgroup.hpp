#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include<string>
#include<SDL_types.h>

using std::string;

class Newsgroup {
  public:
    Newsgroup();
    ~Newsgroup();

    string name;
    Uint64 min_message_no;
    Uint64 max_message_no;

};

#endif
