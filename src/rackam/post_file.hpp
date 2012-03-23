#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include<string>

#include"newsgroup.hpp"

class Newsgroup;
class PostFile {
  public:
    PostFile();
    ~PostFile();

    std::string name;
    unsigned long long int max_message_no;
    unsigned long long int min_message_no;

    Newsgroup *newsgroup;
};

#endif
