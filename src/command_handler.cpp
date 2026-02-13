#include <command_handler.hpp>
#include <string>
#include <iostream>

namespace shell
{
    uint16_t execute(std::string& command)
    {
        if (command == EXIT_COMMAND)
        {
            return 1;
        }
        std::cout << command << ": command not found" << std::endl;
        return 0;
    }

    void repl()
    {
        while (true)
        {
            std::cout << "$ ";
            std::string command;
            std::getline(std::cin, command);
            uint16_t exit_code = execute(command);
            if (exit_code == 1)
            {
                break;
            }
        }
    }
}