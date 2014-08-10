#include "newsgroup.hpp"

#include"post_set.hpp"
#include"post_file.hpp"
#include"author.hpp"
#include"message_header.hpp"
#include"filter.hpp"

using namespace Blackbeard;

Newsgroup::Newsgroup()
{
  max_message_no = 0;
  min_message_no = 0;
  max_author_id = 0;
  pthread_mutex_init(&self_mutex, NULL);
}

Newsgroup::~Newsgroup()
{
  authors_by_name.empty();

  std::vector<Author *>::iterator a;
  for(a = authors.begin(); a != authors.end(); ++a) {
    delete *a;
  }
  authors.empty();

  std::vector<PostSet *>::iterator ps;
  for(ps = postsets.begin(); ps != postsets.end(); ++ps) {
    delete *ps;
  }
  postsets.empty();

  std::vector<PostFile *>::iterator pf;
  for(pf = postfiles.begin(); pf != postfiles.end(); ++pf) {
    delete *pf;
  }
  postfiles.empty();

  std::vector<MessageHeader *>::iterator mh;
  for(mh = headers.begin(); mh != headers.end(); ++mh) {
    delete *mh;
  }
  headers.empty();

  std::vector<Filter *>::iterator f;
  for(f = filters.begin(); f != filters.end(); ++f) {
    delete *f;
  }
  filters.empty();
  pthread_mutex_destroy(&self_mutex);
}

Author *Newsgroup::author_for_name(std::string authorname)
{
  std::map<std::string, Author *>::iterator result;
  result = authors_by_name.find(authorname);
  if(result != authors_by_name.end()){
    return result->second;
  }
  Author *author = new Author(authorname);
  max_author_id++;
  author->id = max_author_id;
  author->newsgroup = this;

  pthread_mutex_lock(&self_mutex);
  authors.push_back(author);
  authors_by_name[authorname] = author;
  pthread_mutex_unlock(&self_mutex);
  return author;
}

Author *Newsgroup::author_for_id(int author_id)
{
  if(author_id > max_author_id){
    return NULL;
  }

  std::vector<Author *>::iterator i;
  for(i = authors.begin() ; i != authors.end() ; ++i) {
    if((*i)->id == author_id)
      return *i;
  }
  return NULL;
}

void Newsgroup::add_filter(std::string filter)
{
  std::vector<Filter *>::iterator i;
  for(i = filters.begin(); i != filters.end(); ++i) {
    if((*i)->text == filter)
      return;
  }
  Filter *new_filter = new Filter();
  new_filter->parse_filter(filter);
  filters.push_back(new_filter);
}
