#include "newsgroup.hpp"

Newsgroup::Newsgroup()
{
  max_message_no = 0;
  min_message_no = 0;
  max_author_id = 0;
}

Newsgroup::~Newsgroup()
{
}

Author *Newsgroup::author_for_name(std::string authorname)
{
  std::vector<Author *>::iterator i;
  for(i = authors.begin() ; i != authors.end() ; ++i) {
    if((*i)->name == authorname)
      return *i;
  }
  Author *author = new Author(authorname);
  max_author_id++;
  author->id = max_author_id;
  authors.push_back(author);
  author->newsgroup = this;
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
