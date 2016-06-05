#include "stringpattern.hpp"

#include <stdlib.h>

using namespace Blackbeard;
using std::string;

StringPattern::StringPattern(unsigned int max_part_no) {
  for (unsigned int i = 0; i < max_part_no + 2; i++) {
    part_order.push_back(31337);
    results.push_back("");
  }
  this->max_part_no = max_part_no;
  name = "";
}

StringPattern::~StringPattern() {}

void StringPattern::add_breaker(string target) { breakers.push_back(target); }

void StringPattern::add_breaker(unsigned int target) {
  part_order[target] = breakers.size();
}

int StringPattern::match(string target) {
  for (unsigned int i = 0; i < max_part_no; i++) {
    results[i] = "";
  }

  unsigned int count = 0;
  auto s = breakers.begin();
  while (s != breakers.end()) {
    size_t index = target.find(*s);

    if (index == string::npos) return 0;

    results[count] = target.substr(0, index);
    target.erase(0, (*s).length() + index);
    count++;
    s++;
  }
  results[count] = target;

  return 1;
}

string StringPattern::get_piece(unsigned int index) {
  if (part_order[index] == 31337) return "";
  return results[part_order[index]];
}

int StringPattern::get_piecen(unsigned int index) {
  string res = get_piece(index);
  return res.compare("") == 0 ? 0 : atoi(res.c_str());
}
