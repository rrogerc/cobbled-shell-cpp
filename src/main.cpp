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

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string raw_input;
    std::stringstream ss;
    std::vector<std::string> input;

    while (1)
    {
        std::cout << "$ ";
        std::getline(std::cin, raw_input);
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
        else
        {
            std::cout << raw_input << ": command not found\n";
        }
    }
}
