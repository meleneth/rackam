#include "controller.hpp"
#include "newsgroup.hpp"
#include "post_file.hpp"
#include "author.hpp"

using namespace Blackbeard;

Controller::Controller() {}

Controller::~Controller() {}

Author_ptr Controller::author_for_name(Newsgroup_ptr newsgroup,
                                      std::string authorname) {
  auto result = (*newsgroup).authors_by_name.find(authorname);
  if (result != (*newsgroup).authors_by_name.end()) {
    return result->second;
  }

  auto author = std::make_shared<Author>(authorname, newsgroup);
  (*newsgroup).max_author_id++;
  author->id = (*newsgroup).max_author_id;

  pthread_mutex_lock(&(*newsgroup).self_mutex);
  (*newsgroup).authors.push_back(author);
  (*newsgroup).authors_by_name[authorname] = author;
  pthread_mutex_unlock(&(*newsgroup).self_mutex);
  return author;
}

PostFile_ptr Controller::find_or_create_postfile_for_filename_fileno(
    Author_ptr author, std::string filename, int fileno) {
  // SHIP IT
  // uh I mean naive implementation here re-write plz

  pthread_mutex_lock(&(*author).self_mutex);  // is this one needed?
  auto result = (*author).postfiles_by_name.find(filename);
  if (result != (*author).postfiles_by_name.end()) {
    pthread_mutex_unlock(&(*author).self_mutex);
    return result->second;
  }
  pthread_mutex_unlock(&(*author).self_mutex);

  std::shared_ptr<PostFile> new_file =
      std::make_shared<PostFile>(filename, author, (*author).newsgroup);

  pthread_mutex_lock(&(*author).self_mutex);
  (*author).max_postfile_id++;
  (*new_file).id = (*author).max_postfile_id;
  (*author).postfiles.push_back(new_file);
  (*author).postfiles_by_name[filename] = new_file;
  pthread_mutex_unlock(&(*author).self_mutex);

  pthread_mutex_lock(&(*author).newsgroup->self_mutex);
  (*author).newsgroup->postfiles.push_back(new_file);
  pthread_mutex_unlock(&(*author).newsgroup->self_mutex);

  return new_file;
}
