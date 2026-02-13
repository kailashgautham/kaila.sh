#include <command_handler.hpp>
#include <string>
#include <iostream>

namespace shell
{
    void execute(std::string& command)
    {
        std::cout << command << ": command not found" << std::endl;
    }

    [[noreturn]] void repl()
    {
        while (true)
        {
            std::cout << "$ ";
            std::string command;
            std::getline(std::cin, command);
            execute(command);
        }
    }
}