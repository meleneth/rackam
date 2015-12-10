#ifndef WEBSTATICFILE_HPP
#define WEBSTATICFILE_HPP

#include <sys/types.h>
#include <rackam_types.hpp>

namespace Blackbeard {

class WebStaticFile {
 public:
  std::string url;
  std::string filename;
  std::string content_type;

  std::vector<char> buffer;
  std::vector<std::string> filters;

  struct timespec st_atim;

  void load_file(std::string filename);
  void compile_coffeescript();
  void reload_if_stale();
  bool is_file_stale();
  void add_filter(std::string filter);
  void apply_filters();
};
}

#endif
