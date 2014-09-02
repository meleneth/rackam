#include "newsgroup.hpp"

#include"post_set.hpp"
#include"post_file.hpp"
#include"author.hpp"
#include"message_header.hpp"
#include"filter.hpp"

using namespace Blackbeard;
using namespace std;

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

  authors.empty();
  postsets.empty();
  postfiles.empty();
  headers.empty();
  filters.empty();

  pthread_mutex_destroy(&self_mutex);
}

shared_ptr<Author> Newsgroup::author_for_id(int author_id)
{
  if(author_id > max_author_id){
    return NULL;
  }

  for(auto author : authors ){
    if(author->id == author_id)
      return author;
  }
  return NULL;
}

void Newsgroup::add_filter(string filter_text)
{
  for(auto filter : filters ){
    if((*filter).text == filter_text)
      return;
  }
  filters.push_back(make_shared<Filter>(filter_text));
}
