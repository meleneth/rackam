#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "rackam_types.hpp"

namespace Blackbeard {
class Controller {
  public:
    Controller();
    ~Controller();

    AuthorPtr author_for_name(NewsgroupPtr newsgroup, std::string authorname);
    PostFilePtr find_or_create_postfile_for_filename_fileno(AuthorPtr author, std::string filename, int fileno);
};
}

#endif
