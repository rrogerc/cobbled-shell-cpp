#ifndef HANDLE_COMMANDS
#define HANDLE_COMMANDS

#include <string>
#include <vector>

void handle_exit(std::string code);
void handle_echo(std::vector<std::string> &args);
void handle_type(std::string command, std::vector<std::string> &path);

#endif
