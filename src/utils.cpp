#include "utils.h"

#include <filesystem>
#include <vector>

void get_path_env(std::vector<std::string> &path) {
    std::string raw_path = std::getenv("PATH");
    // std::cout << raw_path << "\n";

    raw_path += ":";
    while (raw_path.length()) {
        int delimeter = raw_path.find(":");
        path.push_back(raw_path.substr(0, delimeter));
        raw_path.erase(0, delimeter + 1);
    }
}

std::string find_path(std::string command, std::vector<std::string> &path) {
    std::string full_path;
    for (int i = 0; i < path.size(); i++) {
        full_path = path[i] + "/" + command;
        if (std::filesystem::exists(full_path))
            return full_path;
    }
    return "";
}

void parse_input(std::string raw_input, std::vector<std::string> &input) {
    input.clear();
    std::string cur = "";

    raw_input += ' ';

    for (int i = 0; i < raw_input.length(); i++) {
        if (raw_input[i] == '\'' || raw_input[i] == '"') {
            int j = i + 1;
            cur += raw_input[i];
            while (raw_input[j] != raw_input[i]) {
                if (raw_input[i] == '"' && raw_input[j] == '\\')
                    cur += raw_input[j++];
                cur += raw_input[j++];
            }
            cur += raw_input[i];
            i = j;
            input.push_back(cur), cur = "";
        } else if (raw_input[i] != ' ') {
            int j = i;
            while (raw_input[j] != ' ' && raw_input[j] != '\'' && raw_input[j] != '"') {
                if (raw_input[j] == '\\')
                    j++;
                cur += raw_input[j++];
            }
            i = j - 1;
            input.push_back(cur), cur = "";
        } else {
            int j = i;
            while (raw_input[j] == ' ') {
                j++;
            }
            i = j - 1;
            if (input.size() > 0)
                input.push_back(" ");
        }
    }

    // for (auto i : input)
    //     std::cout << i << "\n";
}
