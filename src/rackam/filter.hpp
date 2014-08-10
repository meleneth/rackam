#ifndef FILTER_HPP
#define FILTER_HPP

#include<rackam_types.hpp>

namespace Blackbeard {
class FilterMatch {
  public:
    FilterMatch();
    ~FilterMatch();

    std::string postset_subject;
    int postset_num_files;
    int postset_fileno;
    int postfile_num_pieces;
    int postfile_piece_no;
    std::string postfile_filename;
};

class Filter {
  public:
    Filter();
    ~Filter();

    void parse_filter(std::string filter);
    FilterMatch *match(std::string haystack);

    std::string text;
    std::vector<std::string> filter_pieces;
    long long int num_matched;
    pthread_mutex_t self_mutex;
};
}

#endif
