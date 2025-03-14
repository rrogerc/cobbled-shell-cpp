#include "handle_commands.h"
#include "utils.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
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

    std::string file_output = "";
    std::string output = "";
    int redirect = 0;
    bool append = false;

    for (int i = 2; i < n; i++) {
        if (input[i] == ">" || input[i] == "1>" || input[i] == ">>" || input[i] == "1>>") {
            file_output = input[i + 2];
            redirect = 1;
            if (input[i] == ">>" || input[i] == "1>>")
                append = true;
            break;
        }
        if (input[i] == "2>" || input[i] == "2>>") {
            file_output = input[i + 2];
            redirect = 2;
            if (input[i] == "2>>")
                append = true;
            break;
        }

        if (input[i][0] == '\'' && input[i][input[i].length() - 1] == '\'')
            output += input[i].substr(1, input[i].length() - 2);
        else if (input[i][0] == '\"' && input[i][input[i].length() - 1] == '\"') {
            std::string cur = input[i], cur_parse = "";

            for (int j = 1; j < cur.length() - 1; j++) {
                if (cur[j] == '\\') {
                    cur_parse += cur[++j];
                    continue;
                }
                cur_parse += cur[j];
            }
            output += cur_parse;
        } else
            output += input[i];
    }

    output += "\n";

    if (file_output != "") {

        std::ofstream file;
        if (!append)
            file = std::ofstream(file_output);
        else
            file = std::ofstream(file_output, std::ios_base::app);

        auto cur_buffer = std::cerr.rdbuf();

        if (redirect == 2)
            std::cerr.rdbuf(file.rdbuf());

        if (file.is_open()) {
            if (redirect == 1)
                file << output;
            file.close();
        }
        if (redirect == 2) {
            std::cerr.rdbuf(cur_buffer);
            std::cout << output;
        }
    } else
        std::cout << output;
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
    if (input[0][0] == '\'' || input[0][0] == '"')
        command = input[0].substr(1, command.length() - 2);

    std::string execution_path = find_path(command, path);
    command = input[0];

    if (execution_path == "")
        return false;

    for (int i = 1; i < input.size(); i++)
        command += " " + input[i];

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
