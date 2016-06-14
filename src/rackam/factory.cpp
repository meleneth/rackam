#include<algorithm>

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

void Factory::find_a_home_for(PostFile_ptr post_file)
{
  // If a postfile doesn't have a postset, it is stored on author -> postfiles.
  // If a postfile has a postset, it stored on postset->postfiles, which lives on author->postsets
  // Newsgroup has authors
  // newsgroup browse view should be able to show postsets and postfiles interleaved
  //  based on message id
}

void Factory::rehome(PostFile_ptr child, PostSet_ptr new_home)
{
  auto author = child->author;
  author->postfiles.erase(std::remove_if(author->postfiles.begin(), author->postfiles.end(), *child), author->postfiles.end());
  child->post_set = new_home;
}

