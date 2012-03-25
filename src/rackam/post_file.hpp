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
    long long int max_message_no;
    long long int min_message_no;

    Newsgroup *newsgroup;
};

#endif
