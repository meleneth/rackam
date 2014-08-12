#include "author.hpp"

#include"message_header.hpp"
#include"newsgroup.hpp"
#include"post_file.hpp"
#include"post_set.hpp"

using namespace Blackbeard;

Author::Author(std::string authorname)
{
  this->name = authorname;
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

PostFile *Author::find_or_create_postfile_for_filename_fileno(std::string filename, int fileno) 
{
  // SHIP IT
  // uh I mean naive implementation here re-write plz
  std::map<std::string, PostFile *>::iterator result;

  pthread_mutex_lock(&self_mutex); // is this one needed?
  result = postfiles_by_name.find(filename);
  if(result != postfiles_by_name.end()) {
    pthread_mutex_unlock(&self_mutex);
    return result->second;
  }
  pthread_mutex_unlock(&self_mutex);

  PostFile *new_file = new PostFile();
  new_file->name = filename;
  new_file->author = this;
  new_file->newsgroup = this->newsgroup;

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
