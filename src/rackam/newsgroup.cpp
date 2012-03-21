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
