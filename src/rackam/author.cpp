#include "author.hpp"

#include "message_header.hpp"
#include "newsgroup.hpp"
#include "post_file.hpp"
#include "post_set.hpp"

using namespace Blackbeard;
using namespace std;

Author::Author(std::string authorname, Newsgroup_ptr newsgroup) {
  this->name = authorname;
  this->newsgroup = newsgroup;
  id = 0;
  max_postset_id = 0;
  max_postfile_id = 0;
  size = 0;
  pthread_mutex_init(&self_mutex, NULL);
}

Author::~Author() { pthread_mutex_destroy(&self_mutex); }

PostSet_ptr Author::postset_for_id(int postset_id) {
  if (postset_id > max_postset_id) {
    return NULL;
  }

  for (auto i : postsets) {
    if (i->id == postset_id) return i;
  }
  return NULL;
}

PostFile_ptr Author::postfile_for_id(int postfile_id) {
  if (postfile_id > max_postfile_id) {
    return NULL;
  }

  for (auto i = postfiles.begin(); i != postfiles.end(); ++i) {
    if ((*i)->id == postfile_id) return *i;
  }
  return NULL;
}
