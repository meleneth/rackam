#include "author.hpp"

Author::Author(std::string authorname)
{
  this->name = authorname;
  id = 0;
  max_postset_id = 0;
  max_postfile_id = 0;
  size = 0;
}

Author::~Author()
{
}

PostSet *Author::postset_for_id(int postset_id)
{
  if(postset_id > max_postset_id){
    return NULL;
  }

  std::vector<PostSet *>::iterator i;
  for(i = postsets.begin() ; i != postsets.end() ; ++i) {
    if((*i)->id == postset_id)
      return *i;
  }
  return NULL;
}

PostFile *Author::postfile_for_id(int postfile_id)
{
  if(postfile_id > max_postfile_id){
    return NULL;
  }

  std::vector<PostFile *>::iterator i;
  for(i = postfiles.begin() ; i != postfiles.end() ; ++i) {
    if((*i)->id == postfile_id)
      return *i;
  }
  return NULL;
}
