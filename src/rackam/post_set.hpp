#ifndef POSTSET_HPP
#define POSTSET_HPP

#include"SDL_types.h"

class PostSet {
  public:
    PostSet();
    ~PostSet();

    Uint64 min_message_no;
    Uint64 max_message_no;
};

#endif
