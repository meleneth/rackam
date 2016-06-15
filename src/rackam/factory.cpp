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

// iterator trick:
// make a new iterator type, that can iterate over a newsgroup's posts.
// on init, gets an iterator to postsets and postfiles (which are stored in sorted by msgid order)
// on ++, switch back and forth depending on msgid sort order and return the next item
// Probably requires a PostCollection base class - postfiles and postsets are very similar
// is doing it by date any different than msgid?

void Factory::rehome(PostFile_ptr child, PostSet_ptr new_home)
{
  auto author = child->author;
  author->postfiles.erase(std::remove(author->postfiles.begin(), author->postfiles.end(), child), author->postfiles.end());
  child->postset = new_home;
}

