#include "post_file.hpp"

using namespace Blackbeard;
PostFile::PostFile()
{
  max_message_no = 0;
  min_message_no = 0;
  size = 0;
  pthread_mutex_init(&self_mutex, NULL);
  newsgroup = nullptr;
  author = nullptr;
}

PostFile::~PostFile()
{
  pthread_mutex_destroy(&self_mutex);
}
