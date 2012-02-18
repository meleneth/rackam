#ifndef NEWSGROUP_HPP
#define NEWSGROUP_HPP

#include<string>

using std::string;

class Newsgroup {
  public:
    Newsgroup();
    ~Newsgroup();

    string name;
    unsigned long long int min_message_no;
    unsigned long long int max_message_no;

};

#endif
