#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "rackam_types.hpp"

namespace Blackbeard {
class Controller {
 public:
  Controller();
  ~Controller();

  Author_ptr author_for_name(Newsgroup_ptr newsgroup, std::string authorname);
  PostFile_ptr find_or_create_postfile_for_filename_fileno(Author_ptr author,
                                                          std::string filename,
                                                          int fileno);
};
}

#endif
