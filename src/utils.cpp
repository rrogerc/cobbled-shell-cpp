#include "utils.h"

#include <filesystem>
#include <vector>

void get_path_env(std::vector<std::string> &path)
{
    std::string raw_path = std::getenv("PATH");
    // std::cout << raw_path << "\n";

    raw_path += ":";
    while (raw_path.length())
    {
        int delimeter = raw_path.find(":");
        path.push_back(raw_path.substr(0, delimeter));
        raw_path.erase(0, delimeter + 1);
    }
}

std::string find_path(std::string command, std::vector<std::string> &path)
{
    std::string full_path;
    for (int i = 0; i < path.size(); i++)
    {
        full_path = path[i] + "/" + command;

        if (std::filesystem::exists(full_path))
            return full_path;
    }
    return "";
}

#include <iostream>

void parse_input(std::string raw_input, std::vector<std::string> &input)
{
    input.clear();
    std::string cur = "";
    bool is_quote = false;

    raw_input += ' ';

    for (int i = 0; i < raw_input.length(); i++)
    {
        if (raw_input[i] == '\'' || raw_input[i] == '"')
        {
            int j = i + 1;
            while (raw_input[j] != raw_input[i])
                cur += raw_input[j++];
            i = j;
            continue;
        }

        if (is_quote || raw_input[i] != ' ')
            cur += raw_input[i];
        else if (cur != "")
            input.push_back(cur), cur = "";
    }

    // for (auto i : input)
    //     std::cout << i << "\n";
}
