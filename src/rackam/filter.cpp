#include <stdio.h>
#include <stdlib.h>

#include "filter.hpp"
#include "console.hpp"

using namespace Blackbeard;
using namespace std;

FilterMatch::FilterMatch() {
  postset_subject.clear();
  postset_num_files = 0;
  postset_fileno = 0;
  postfile_num_pieces = 0;
  postfile_piece_no = 0;
  postfile_filename.clear();
}

FilterMatch::~FilterMatch() {}

Filter::Filter() {
  pthread_mutex_init(&self_mutex, NULL);
  num_matched = 0;
}

Filter::Filter(std::string filter_text) : Filter() {
  parse_filter(filter_text);
}

Filter::~Filter() { pthread_mutex_destroy(&self_mutex); }

void Filter::parse_filter(std::string filter) {
  text = filter;
  filter_pieces.clear();

  int position = 0;
  int size = filter.size();
  while (position < size) {
    int result = filter.find('%', position);
    if (result != std::string::npos) {
      // don't add to the filter if the first piece is a flag
      if (result != 0) {
        filter_pieces.push_back(filter.substr(position, result - position));
      }
      filter_pieces.push_back(filter.substr(result, 2));
      position = result + 2;
    } else {
      filter_pieces.push_back(filter.substr(position, size - position));
      position = size;
    }
  }
}

shared_ptr<FilterMatch> Filter::match(std::string haystack) {
  int needle_position = 0;
  int match_position = 0;
  int size = filter_pieces.size();

  std::string postset_subject;
  int postset_num_files;
  int postset_fileno;
  int postfile_num_pieces;
  int postfile_piece_no;
  std::string postfile_filename;

  if (0 == size) return NULL;

  std::string match_fragment = filter_pieces[0];
  // Match engine is written for %field followed by a match, so match any
  // leading
  // fragment first.  This means following one % with another will not work,
  // there must
  // be an intervening natural text match. (i.e. %a%b is bad, %a,%b is ok)
  if ('%' != match_fragment.at(0)) {
    int result = haystack.find(match_fragment);
    if (std::string::npos == result) {
      return NULL;
    }
    if (0 != result) {
      return NULL;
    }
    needle_position++;
    match_position = match_fragment.length();
  }

  // Main match engine.  Finding content for our current %block by looking for
  // the next
  // match and then handling the match and incrementing the state machine
  while (needle_position < size) {
    match_fragment = filter_pieces[needle_position];
    std::string percent_matched;
    if ('%' == match_fragment.at(0)) {
      std::string match_percent = match_fragment;

      if (needle_position + 1 < filter_pieces.size()) {
        match_fragment = filter_pieces[needle_position + 1];

        int result = haystack.find(match_fragment, match_position);
        if (std::string::npos == result) {
          return NULL;
        }
        percent_matched =
            haystack.substr(match_position, result - match_position);
        match_position = result + match_fragment.length();
      } else {
        percent_matched = haystack.substr(match_position, haystack.length());
      }
      switch (match_percent.at(1)) {
        case 'f':
          postset_num_files = atoi(percent_matched.c_str());
          break;
        case 'e':
          postset_fileno = atoi(percent_matched.c_str());
          break;
        case 'n':
          postfile_num_pieces = atoi(percent_matched.c_str());
          break;
        case 'p':
          postfile_piece_no = atoi(percent_matched.c_str());
          break;
        case 'a':
          postfile_filename = percent_matched;
          break;
        case 's':
          postset_subject = percent_matched;
          break;
        case 'd':
          break;
        default:
          console->log("Unhandled percent flag: " + match_percent.at(1));
      }

      needle_position += 2;
    } else {
      console->log("Matcher very confused.  %flag at end of filter?");
    }
  }

  auto match = make_shared<FilterMatch>();
  match->postset_subject = postset_subject;
  match->postset_num_files = postset_num_files;
  match->postset_fileno = postset_fileno;
  match->postfile_num_pieces = postfile_num_pieces;
  match->postfile_piece_no = postfile_piece_no;
  match->postfile_filename = postfile_filename;

  pthread_mutex_lock(&self_mutex);
  num_matched++;
  pthread_mutex_unlock(&self_mutex);

  return match;
}
