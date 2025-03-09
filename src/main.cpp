#include "utils.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

void handle_exit(std::string code)
{
    int error_code;
    // std::cout << " ::: " << code << " ::: \n";
    try
    {
        error_code = stoi(code);
    }
    catch (std::exception &e)
    {
        error_code = 0;
    }

    exit(error_code);
}

void handle_echo(std::vector<std::string> &args)
{
    int n = args.size();

    for (int i = 1; i < n; i++)
        std::cout << args[i] << " ";
    std::cout << "\n";
}

void handle_type(std::string command, std::vector<std::string> &path)
{
    std::vector<std::string> builtins = {"echo", "type", "exit"};

    for (auto i : builtins)
    {
        // std::cout << i << " :\n";
        if (command == i)
        {
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

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string raw_input;
    std::stringstream ss;
    std::vector<std::string> input;

    std::vector<std::string> path;
    get_path_env(path);

    // for (auto i : path)
    //     std::cout << i << "\n";

    while (1)
    {
        std::cout << "$ ";

        std::getline(std::cin, raw_input);
        ss.clear();
        ss.str(raw_input);
        input.clear();

        std::string tmp;
        while (ss >> tmp)
            input.push_back(tmp);

        if (input.size() == 0)
            break;

        if (input[0] == "exit")
        {
            handle_exit((input.size() == 1 ? "0" : input[1]));
        }
        else if (input[0] == "echo")
        {
            handle_echo(input);
        }
        else if (input[0] == "type")
        {
            if (input.size() == 1)
                continue;
            handle_type(input[1], path);
        }
        else
        {
            std::cout << raw_input << ": command not found\n";
        }
    }
}
