#include "handle_commands.h"
#include "utils.h"

#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

void handle_exit(std::string code) {
    int error_code;
    // std::cout << " ::: " << code << " ::: \n";
    try {
        error_code = stoi(code);
    } catch (std::exception &e) {
        error_code = 0;
    }

    exit(error_code);
}

void handle_echo(std::vector<std::string> &input) {
    int n = input.size();
    std::set<char> special_back = {'\\', '$', '\"'};

    for (int i = 2; i < n; i++) {
        if (input[i][0] == '\'' && input[i][input[i].length() - 1] == '\'')
            std::cout << input[i].substr(1, input[i].length() - 2);
        else if (input[i][0] == '\"' && input[i][input[i].length() - 1] == '\"') {
            std::string cur = input[i], cur_parse = "";

            for (int j = 1; j < cur.length() - 1; j++) {
                if (cur[j] == '\\') {
                    cur_parse += cur[++j];
                    continue;
                }
                cur_parse += cur[j];
            }
            std::cout << cur_parse;
        } else
            std::cout << input[i];
    }

    std::cout << "\n";
}

void handle_type(std::string command, std::vector<std::string> &path) {
    std::vector<std::string> builtins = {"echo", "type", "exit", "pwd"};

    for (auto i : builtins) {
        // std::cout << i << " :\n";
        if (command == i) {
            std::cout << command << " is a shell builtin\n";
            return;
        }
    }

    std::string path_env_location = find_path(command, path);

    if (path_env_location == "")
        std::cout << command << ": not found\n";
    else
        std::cout << command << " is " << path_env_location << "\n";
}

bool handle_execution(std::vector<std::string> &input, std::vector<std::string> &path) {

    std::string command = input[0];
    // if (input[0][0] == '\'' || input[0][0] == '"') {
    //     command = input[0].substr(1, command.length() - 2);
    //     std::cout << "ASDASD\n";
    // }
    // std::cout << command << "  asd\n";

    std::string execution_path = find_path(command, path);
    if (execution_path == "")
        return false;

    for (int i = 1; i < input.size(); i++)
        command += " " + input[i];

    // std::cout << command << "\n";

    std::system(command.c_str());

    return true;
}

void handle_pwd() {
    std::cout << std::filesystem::current_path().string() << "\n";
}

void handle_cd(std::vector<std::string> &input) {
    std::string to_string = (input.size() <= 2 ? "~" : input[2]);

    if (to_string == "~")
        to_string = std::getenv("HOME");

    std::filesystem::path to(to_string);

    try {
        std::filesystem::current_path(to);
    } catch (std::exception &e) {
        std::cout << "cd: " << to_string << ": No such file or directory\n";
    }
}
