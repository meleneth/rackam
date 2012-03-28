#include "newsgroup.hpp"

Newsgroup::Newsgroup()
{
//  max_message_no = 0;
//  min_message_no = 0;
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
  authors.push_back(author);
  author->newsgroup = this;
  return author;
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
