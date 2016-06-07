#include "factory.hpp"
#include "newsgroup.hpp"
#include "author.hpp"
#include "post_file.hpp"
#include "rackam.hpp"

using namespace Blackbeard;

Newsgroup_ptr Factory::make_Newsgroup(std::string name)
{
  return rackam->newsgroup_for_name(name);
}

Author_ptr    Factory::make_Author(std::string author_name, Newsgroup_ptr newsgroup)
{
  return newsgroup->author_for_name(author_name);
}

PostFile_ptr  Factory::make_PostFile(Newsgroup_ptr newsgroup, Author_ptr author, std::string filename, int size)
{
  auto post_file = std::make_shared<PostFile>(filename, author, newsgroup);
  post_file->size = size;
  return post_file;
}

