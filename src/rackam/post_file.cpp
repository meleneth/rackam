#include "post_file.hpp"

using namespace Blackbeard;
using namespace std;

PostFile::PostFile()
{
  max_message_no = 0;
  min_message_no = 0;
  size = 0;
  pthread_mutex_init(&self_mutex, NULL);
  newsgroup = nullptr;
  author = nullptr;
}

PostFile::PostFile(std::string name, shared_ptr<Author> author, shared_ptr<Newsgroup> newsgroup):PostFile()
{
  this->name = name;
  this->author = author;
  this->newsgroup = newsgroup;
}

PostFile::~PostFile()
{
  pthread_mutex_destroy(&self_mutex);
}
