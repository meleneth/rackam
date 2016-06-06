#include "factory.hpp"

using namespace Blackbeard;

Newsgroup_ptr Factory::make_Newsgroup(std::string name)
{
}

Author_ptr    Factory::make_Author(std::string author_name, Newsgroup_ptr newsgroup)
{
}

PostFile_ptr  Factory::make_PostFile(Newsgroup_ptr newsgroup, Author_ptr author, std::string filename, int size)
{
}

