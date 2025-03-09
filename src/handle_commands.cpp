#include "handle_commands.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>
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

bool handle_execution(std::vector<std::string> &input, std::vector<std::string> &path)
{

    std::string execution_path = find_path(input[0], path);

    if (execution_path == "")
        return false;

    for (int i = 1; i < input.size(); i++)
        execution_path += " " + input[i];

    std::system(execution_path.c_str());

    return true;
}
