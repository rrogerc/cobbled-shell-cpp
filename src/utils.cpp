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

void parse_input(std::string raw_input, std::vector<std::string> &input)
{
    std::string cur = "";
    bool is_quote = false;

    for (int i = 0; i < raw_input.length(); i++)
    {
        if (raw_input[i] == '\'')
        {
            if (is_quote)
                input.push_back(cur), cur = "";
            else
                is_quote = true;
            is_quote = !is_quote;
            continue;
        }

        if (is_quote)
            cur += raw_input[i];
        else if (raw_input[i] != ' ')
            cur += raw_input[i];
        else if (cur != "")
            input.push_back(cur), cur = "";
    }
}
