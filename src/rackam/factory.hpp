#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <rackam_types.hpp>

namespace Blackbeard {

class Factory {
  public:
    static Newsgroup_ptr make_Newsgroup(std::string name);
    static Author_ptr make_Author(std::string author_name, Newsgroup_ptr newsgroup);
    static PostFile_ptr make_PostFile(Newsgroup_ptr newsgroup, Author_ptr author, std::string filename, int size);
    static void find_a_home_for(PostFile_ptr post_file);
    static void rehome(PostFile_ptr child, PostSet_ptr new_home);
};

}
#endif
