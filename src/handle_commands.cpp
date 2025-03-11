#include "handle_commands.h"
#include "utils.h"

#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
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

void handle_echo(std::vector<std::string> &input)
{
    int n = input.size();
    std::set<char> special_back = {'\\', '$', '\"'};

    for (int i = 1; i < n; i++)
    {
        if (input[i][0] == '\'')
            std::cout << input[i].substr(1, input[i].length() - 2);
        else if (input[i][0] == '\"')
        {
            std::vector<std::string> parsed;
            std::string cur = input[i], cur_parse = "";

            while (cur.length())
            {
                if (cur[0] == '\"')
                {
                    int j = cur.find('\"', 1);
                    while (cur[j - 1] == '\\')
                        j = cur.find('\"', j + 1);

                    // std::cout << cur << " asd\n";

                    std::string tmp = "";
                    for (int k = 1; k < j; k++)
                    {
                        if (cur[k] == '\\' && special_back.count(cur[k + 1]))
                            continue;
                        tmp += cur[k];
                    }

                    // parsed.push_back(cur.substr(1, j - 1));
                    parsed.push_back(tmp);
                    cur.erase(0, j + 1);
                }
                else
                {
                    int j = cur.find('\"', 1);
                    while (cur[j - 1] == '\\' && j != std::string::npos)
                        j = cur.find('\"', j + 1);

                    if (j == std::string::npos)
                    {
                        parsed.push_back(cur.substr(0));
                        cur.erase(0);
                    }
                    else
                    {
                        parsed.push_back(cur.substr(0, j));
                        cur.erase(0, j + 1);
                    }
                }
            }
            for (auto i : parsed)
                std::cout << i;
            std::cout << " ";
        }
        else
            std::cout << input[i] << " ";
    }

    std::cout << "\n";
}

void handle_type(std::string command, std::vector<std::string> &path)
{
    std::vector<std::string> builtins = {"echo", "type", "exit", "pwd"};

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

    std::string command = input[0];

    for (int i = 1; i < input.size(); i++)
        command += " " + input[i];

    // std::cout << command << "\n";

    std::system(command.c_str());

    return true;
}

void handle_pwd()
{
    std::cout << std::filesystem::current_path().string() << "\n";
}

void handle_cd(std::vector<std::string> &input)
{
    std::string to_string = (input.size() == 1 ? "~" : input[1]);

    if (to_string == "~")
        to_string = std::getenv("HOME");

    std::filesystem::path to(to_string);

    try
    {
        std::filesystem::current_path(to);
    }
    catch (std::exception &e)
    {
        std::cout << "cd: " << to_string << ": No such file or directory\n";
    }
}
