#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include "default_init_allocator.hpp"
#include "pstream.h"

#include "web_static_file.hpp"

using namespace Blackbeard;

void WebStaticFile::load_file(std::string filename) {
  struct stat file_stats;
  stat(filename.c_str(), &file_stats);
  st_atim = file_stats.st_atim;

  auto num_bytes = file_stats.st_size;
  buffer.resize(num_bytes);

  std::ifstream infile;
  infile.open(filename, std::ios::binary | std::ios::in);
  infile.read(&buffer[0], num_bytes);
  infile.close();

  this->filename = filename;

  apply_filters();
}

bool WebStaticFile::is_file_stale() {
  struct stat file_stats;
  stat(filename.c_str(), &file_stats);
  return st_atim.tv_sec < file_stats.st_atim.tv_sec;
}

void WebStaticFile::reload_if_stale() {
  if (is_file_stale()) {
    load_file(filename);
  }
}

void WebStaticFile::compile_coffeescript() {
  using namespace redi;
  std::vector<char, default_init_allocator<char>> temp_buffer;

  const pstreams::pmode mode = pstreams::pstdout | pstreams::pstdin;
  pstream child("coffee -p -s", mode);
  child.write(&buffer[0], buffer.size());
  child << peof;

  temp_buffer.reserve(256000);
  child.out().read(&temp_buffer[0], temp_buffer.capacity());

  auto num_bytes = child.out().gcount();
  temp_buffer.resize(num_bytes);
  buffer.resize(num_bytes + 1);
  buffer.assign(begin(temp_buffer), end(temp_buffer));
  buffer[num_bytes] = 0;
}

void WebStaticFile::add_filter(std::string filter) {
  // LOG(INFO) << "Added filter: " << filter;
  filters.push_back(filter);
}

void WebStaticFile::apply_filters() {
  using namespace redi;
  const pstreams::pmode mode = pstreams::pstdout | pstreams::pstdin;
  std::vector<char, default_init_allocator<char>> temp_buffer;
  temp_buffer.reserve(256000);

  for (auto filter : filters) {
    pstream child(filter, mode);
    child.write(&buffer[0], buffer.size());
    child << peof;

    child.out().read(&temp_buffer[0], temp_buffer.capacity());

    auto num_bytes = child.out().gcount();
    temp_buffer.resize(num_bytes);
    buffer.resize(num_bytes);
    buffer.assign(begin(temp_buffer), end(temp_buffer));
  }
}
