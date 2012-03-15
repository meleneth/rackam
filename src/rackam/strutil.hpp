#ifndef ___strutil_inc
#define ___strutil_inc 1

#include <string>
#include <algorithm>
#include <vector>

void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
std::string bitviz(unsigned int showme);
std::string trimmed(std::string shaggy);
unsigned int is_whitespace(char c);
std::string get_crc_32(std::string process_me);
void generate_crc_table(unsigned int *table);
std::string replace_all_substrings(std::string from_me, std::string take_me, std::string for_me);
std::string replace_substrings(std::string from_me, std::string take_me, std::string for_me);

std::string xml_escape(std::string escape_me);
std::string xml_unescape(std::string unescape_me);
std::string js_escape(std::string escape_me);
std::string safe_dirname(std::string unsafe);
std::string human_readable_bytes(unsigned long long int num_bytes);

std::string file_extension(std::string filename);

#endif
