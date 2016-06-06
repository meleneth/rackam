#include "headers_parser.hpp"

#include "strutil.hpp"
#include "newsgroup.hpp"
#include "controller.hpp"
#include "message_header.hpp"
#include "author.hpp"
#include "post_file.hpp"
#include "filter.hpp"

#define HEADERSPARSER_WORKSIZE 5000

using namespace Blackbeard;
using namespace std;

HeadersParser::HeadersParser(Newsgroup_ptr newsgroup) {
  pthread_mutex_init(&self_mutex, NULL);
  running_threads = 0;
  this->newsgroup = newsgroup;
}

HeadersParser::~HeadersParser() { pthread_mutex_destroy(&self_mutex); }

void HeadersParser::process_line(std::string line) {
  std::vector<std::string> header_pieces;
  unsigned int i;

  Tokenize(line, header_pieces, "\t");

  if (header_pieces.size() < 8) return;
  if (header_pieces.size() > 9) return;

  std::string msg_id = header_pieces[4];
  msg_id = msg_id.substr(1, msg_id.length() - 2);
  std::string subject = header_pieces[1];
  Controller c;
  auto posted_by = c.author_for_name(newsgroup, header_pieces[2]);

  auto header = make_shared<MessageHeader>(
      newsgroup, atoll(header_pieces[0].c_str()), msg_id, subject, posted_by,
      atoi(header_pieces[5].c_str()));

  for (auto filter : header->group->filters) {
    FilterMatch_ptr match = filter->match(header->subject);
    if (match) {
      if ((match->postset_num_files != 0) &&
          (match->postfile_num_pieces != 0) &&
          (match->postfile_filename.length() != 0)) {
        // Start at the beginning.  Just make PostFile, don't even need to
        // actually
        // keep the message id's yet

        // This will all run through the database somehow soon, don't worry
        // about it.

        // Don't worry about it he says, do you even KNOW what that did to
        // threading...
        Controller c;
        auto file = c.find_or_create_postfile_for_filename_fileno(
            header->author, match->postfile_filename, 0);

        // omg denormalized someone shoot me
        pthread_mutex_lock(&file->self_mutex);
        file->size += header->size;
        pthread_mutex_unlock(&file->self_mutex);

        pthread_mutex_lock(&header->author->self_mutex);
        header->author->size += header->size;
        pthread_mutex_unlock(&header->author->self_mutex);

        pthread_mutex_lock(&header->author->newsgroup->self_mutex);
        header->author->newsgroup->size += header->size;
        pthread_mutex_unlock(&header->author->newsgroup->self_mutex);

        return;
      }
    }
  }

  pthread_mutex_lock(&header->group->self_mutex);
  header->group->headers.push_back(header);
  pthread_mutex_unlock(&header->group->self_mutex);

  pthread_mutex_lock(&header->author->self_mutex);
  header->author->headers.push_back(header);
  header->author->size += header->size;
  pthread_mutex_unlock(&header->author->self_mutex);
}

namespace Blackbeard {
void *HeadersParser_process_lines(void *s);
}

void HeadersParser::queue_line(std::string line) {
  static std::vector<std::string> *headers = NULL;
  pthread_t new_thread;

  if (!headers) {
    headers = new std::vector<std::string>;
  }

  if (line.length() == 0) {
    // Special argument!  info == NULL, flush our headers
    if (headers) {
      pthread_mutex_lock(&self_mutex);
      running_threads++;
      pthread_mutex_unlock(&self_mutex);
      HeadersParser_thread_info_t *thread_data =
          new HeadersParser_thread_info_t;
      thread_data->parser = this;
      thread_data->headers = headers;

      pthread_create(&new_thread, NULL, HeadersParser_process_lines,
                     (void *)thread_data);
      pthread_detach(new_thread);
    }

    if (running_threads) {
      pthread_mutex_lock(&self_mutex);
    }
    while (running_threads) {
      pthread_mutex_unlock(&self_mutex);
      sched_yield();
      pthread_mutex_lock(&self_mutex);
    }
    return;
  }

  headers->push_back(line);

  if (headers->size() > HEADERSPARSER_WORKSIZE) {
    HeadersParser_thread_info_t *thread_data = new HeadersParser_thread_info_t;
    thread_data->parser = this;
    thread_data->headers = headers;

    pthread_create(&new_thread, NULL, HeadersParser_process_lines,
                   (void *)thread_data);
    pthread_detach(new_thread);

    pthread_mutex_lock(&self_mutex);
    running_threads++;
    pthread_mutex_unlock(&self_mutex);

    headers = NULL;
  }
}

namespace Blackbeard {
void *HeadersParser_process_lines(void *s) {
  HeadersParser_thread_info_t *thread_data = (HeadersParser_thread_info_t *)s;

  std::vector<std::string> *headers = thread_data->headers;

  std::vector<std::string>::iterator i;
  for (i = headers->begin(); i != headers->end(); ++i) {
    thread_data->parser->process_line(*i);
  }

  pthread_mutex_lock(&thread_data->parser->self_mutex);
  thread_data->parser->running_threads--;
  pthread_mutex_unlock(&thread_data->parser->self_mutex);
  delete thread_data->headers;
  delete thread_data;
}
}
