#include "handle_commands.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string raw_input;
    std::vector<std::string> input;

    std::vector<std::string> path;
    get_path_env(path);

    while (1)
    {
        std::cout << "$ ";
        std::getline(std::cin, raw_input);
        parse_input(raw_input, input);

        if (input.size() == 0)
            break;

        // for (auto i : input)
        //     std::cout << i << "\n";

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
        else if (input[0] == "pwd")
        {
            handle_pwd();
        }
        else if (input[0] == "cd")
        {
            handle_cd(input);
        }
        else
        {
            if (!handle_execution(input, path))
                std::cout << raw_input << ": command not found\n";
        }
    }
}
