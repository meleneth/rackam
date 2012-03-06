#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include"post_set.hpp"

#include<string>
#include<map>

using std::string;
using std::map;

class PostSet;
class Newsgroup {
  public:
    Newsgroup();
    ~Newsgroup();

    string name;
    unsigned long long int min_message_no;
    unsigned long long int max_message_no;

    map<void *, PostSet *> postsets;
};

#endif
