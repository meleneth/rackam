#ifndef FILTER_HPP
#define FILTER_HPP

#include<string>
#include<vector>

class Filter {
  public:
    Filter();
    ~Filter();

    void parse_filter(std::string filter);
    bool match(std::string haystack);

    std::string text;
    std::vector<std::string> filter_pieces;

    int postset_num_files;
    int postset_fileno;
    int postfile_num_pieces;
    int postfile_piece_no;
    std::string postfile_filename;
};

#endif
