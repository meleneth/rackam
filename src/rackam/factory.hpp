#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <rackam_types.hpp>

namespace Blackbeard {

class Factory {
  static Newsgroup_ptr make_Newsgroup(std::string name);
  static Author_ptr make_Author(std::string author_name, Newsgroup_ptr newsgroup);
  static PostFile_ptr make_PostFile(Newsgroup_ptr newsgroup, Author_ptr author, std::string filename, int size);
};

}
#endif
