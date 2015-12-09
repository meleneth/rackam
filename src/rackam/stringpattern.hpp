#ifndef ___stringpattern_inc
#define ___stringpattern_inc 1

#include <rackam_types.hpp>

namespace Blackbeard {
class StringPattern {
 public:
  // Public data members go here.
  StringPattern(unsigned int max_part_no);
  ~StringPattern();

  void add_breaker(std::string pattern);
  void add_breaker(unsigned int part_no);

  int match(std::string target);

  std::string get_piece(unsigned int index);
  int get_piecen(unsigned int index);

  std::list<std::string> breakers;
  std::vector<unsigned int> part_order;
  unsigned int max_part_no;

  std::vector<std::string> results;
  std::string name;

 private:
  // Private members go here.
 protected:
  // Protected members go here.
};
}

#endif
