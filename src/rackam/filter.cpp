#include "filter.hpp"
#include<stdio.h>

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
      filter_pieces.push_back(filter.substr(position, result - position));
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
}


