#include<stdio.h>
#include<stdlib.h>

#include "filter.hpp"
#include "console.hpp"

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::parse_filter(std::string filter)
{
  text = filter;
  filter_pieces.clear();

  int position = 0;
  int size = filter.size();
  while(position < size) {
    int result = filter.find('%', position);
    if(result != std::string::npos) {
      // don't add to the filter if the first piece is a flag
      if(result != 0){
        filter_pieces.push_back(filter.substr(position, result - position));
      }
      filter_pieces.push_back(filter.substr(result, 2));
      position = result + 2;
    }else{
      filter_pieces.push_back(filter.substr(position, size - position));
      position = size;
    }
  }
  
}

bool Filter::match(std::string haystack)
{
  int needle_position = 0;
  int match_position = 0;
  int size = filter_pieces.size();

  if(0 == size)
    return false;

  std::string match_fragment = filter_pieces[0];
  // Match engine is written for %field followed by a match, so match any leading 
  // fragment first.  This means following one % with another will not work, there must
  // be an intervening natural text match. (i.e. %a%b is bad, %a,%b is ok)
  if('%' != match_fragment.at(0)) {
    int result = haystack.find(match_fragment);
    if(std::string::npos == result) {
      return false;
    }
    if(0 != result){
      return false;
    }
    needle_position++;
    match_position = match_fragment.length();
  }

  // Main match engine.  Finding content for our current %block by looking for the next
  // match and then handling the match and incrementing the state machine
  while(needle_position < size) {
    match_fragment = filter_pieces[needle_position];
    if('%' == match_fragment.at(0)) {
      std::string match_percent = match_fragment;
      match_fragment = filter_pieces[needle_position + 1];

      int result = haystack.find(match_fragment, match_position);
      if(std::string::npos == result) {
        return false;
      }
      std::string percent_matched = haystack.substr(match_position, result - match_position);
      switch(match_percent.at(1)) {
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
        
        match_position = result + match_fragment.length();
        needle_position += 2;
      } else {
        console->log("Matcher very confused.  %flag at end of filter?");
      }
    }

  return true;
}


