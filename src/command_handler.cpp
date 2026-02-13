#include <command_handler.hpp>
#include <string>
#include <iostream>

void update()
{
    while (true)
    {
        std::string command;
        std::cin >> command;
        std:: cout << command << ": command not found" << std::endl;
    }
}