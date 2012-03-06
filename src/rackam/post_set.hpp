#ifndef POSTSET_HPP
#define POSTSET_HPP

#include<map>

using std::map;

#include "post_file.hpp"

class PostFile;
class PostSet {
  public:
    PostSet();
    ~PostSet();

    unsigned long long int min_message_no;
    unsigned long long int max_message_no;
    map<void *, PostFile *> postfiles;
};

#endif
