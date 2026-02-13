#include <command_handler.hpp>
#include <string>
#include <iostream>

namespace shell
{
    void update()
    {
        std::string command;
        std::getline(std::cin, command);
        std::cout << command << ": command not found" << std::endl;
    }
}