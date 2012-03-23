#ifndef POSTSET_HPP
#define POSTSET_HPP

#include<map>
#include<string>

#include "post_file.hpp"

class PostFile;
class PostSet {
  public:
    PostSet();
    ~PostSet();

    unsigned long long int min_message_no;
    unsigned long long int max_message_no;
    std::map<void *, PostFile *> postfiles;

    std::string subject;
};

#endif
