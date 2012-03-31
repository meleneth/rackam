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

    long long int min_message_no;
    long long int max_message_no;
    long long int size;
    int id;
    std::map<void *, PostFile *> postfiles;

    std::string subject;
};

#endif
