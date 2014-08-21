#include "author.hpp"

#include"message_header.hpp"
#include"newsgroup.hpp"
#include"post_file.hpp"
#include"post_set.hpp"

using namespace Blackbeard;
using namespace std;

Author::Author(std::string authorname, shared_ptr<Newsgroup> newsgroup)
{
  this->name = authorname;
  this->newsgroup = newsgroup;
  id = 0;
  max_postset_id = 0;
  max_postfile_id = 0;
  size = 0;
  pthread_mutex_init(&self_mutex, NULL);
}

Author::~Author()
{
  pthread_mutex_destroy(&self_mutex);
}

shared_ptr<PostSet> Author::postset_for_id(int postset_id)
{
  if(postset_id > max_postset_id){
    return NULL;
  }

  std::vector<PostSet *>::iterator i;
  for(auto i : postsets) {
    if(i->id == postset_id)
      return i;
  }
  return NULL;
}

std::shared_ptr<PostFile> Author::postfile_for_id(int postfile_id)
{
  if(postfile_id > max_postfile_id){
    return NULL;
  }

  for(auto i = postfiles.begin() ; i != postfiles.end() ; ++i) {
    if((*i)->id == postfile_id)
      return *i;
  }
  return NULL;
}

shared_ptr<PostFile> Author::find_or_create_postfile_for_filename_fileno(std::string filename, int fileno) 
{
  // SHIP IT
  // uh I mean naive implementation here re-write plz

  pthread_mutex_lock(&self_mutex); // is this one needed?
  auto result = postfiles_by_name.find(filename);
  if(result != postfiles_by_name.end()) {
    pthread_mutex_unlock(&self_mutex);
    return result->second;
  }
  pthread_mutex_unlock(&self_mutex);

  std::shared_ptr<PostFile> new_file = std::make_shared<PostFile>(filename, shared_from_this(), newsgroup);

  pthread_mutex_lock(&self_mutex);
  max_postfile_id++;
  new_file->id = max_postfile_id;
  postfiles.push_back(new_file);
  postfiles_by_name[filename] = new_file;
  pthread_mutex_unlock(&self_mutex);

  pthread_mutex_lock(&newsgroup->self_mutex);
  newsgroup->postfiles.push_back(new_file);
  pthread_mutex_unlock(&newsgroup->self_mutex);

  return new_file;
}
