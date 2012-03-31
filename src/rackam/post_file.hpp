#ifndef POSTFILE_HPP
#define POSTFILE_HPP

#include<string>

#include"newsgroup.hpp"
#include"author.hpp"

class Newsgroup;
class Author;
class PostFile {
  public:
    PostFile();
    ~PostFile();

    std::string name;
    long long int max_message_no;
    long long int min_message_no;
    long long int size;
    int id;

    Newsgroup *newsgroup;
    Author *author;
};

#endif
