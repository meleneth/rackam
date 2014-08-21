#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include<rackam_types.hpp>

namespace Blackbeard {
class Author : public std::enable_shared_from_this < Author > {
  public:
    Author(std::string name, std::shared_ptr<Newsgroup> newsgroup);
    ~Author();
    std::shared_ptr<PostSet> postset_for_id(int postset_id);
    std::shared_ptr<PostFile> postfile_for_id(int postfile_id);
    std::shared_ptr<PostFile> find_or_create_postfile_for_filename_fileno(std::string filename, int fileno);

    std::string name;
    long long int size;
    int id;
    int max_postset_id;
    int max_postfile_id;

    pthread_mutex_t self_mutex;

    std::shared_ptr<Newsgroup> newsgroup;

    MessageHeader_vector headers;
    PostSet_vector postsets;
    PostFile_vector postfiles;
    StringToPostFileMap postfiles_by_name;
};

}

#endif
