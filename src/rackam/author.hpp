#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include<rackam_types.hpp>

namespace Blackbeard {
class Author {
  public:
    Author(std::string name);
    ~Author();
    PostSet   *postset_for_id(int postset_id);
    PostFile *postfile_for_id(int postfile_id);
    PostFile *find_or_create_postfile_for_filename_fileno(std::string filename, int fileno);

    std::string name;
    long long int size;
    int id;
    int max_postset_id;
    int max_postfile_id;

    pthread_mutex_t self_mutex;

    Newsgroup *newsgroup;

    MessageHeaderVector headers;
    PostSetVector postsets;
    PostFileVector postfiles;
    StringToPostFileMap postfiles_by_name;
};

}

#endif
