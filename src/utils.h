#ifndef UTILS
#define UTILS

#include <string>
#include <vector>

void get_path_env(std::vector<std::string> &path);
std::string find_path(std::string command, std::vector<std::string> &path);

#endif
