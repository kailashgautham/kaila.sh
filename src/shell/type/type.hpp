#pragma once

#include <string>
#include <iostream>
#include <common/commands.hpp>

namespace shell::type
{
    int16_t execute(const std::string& command)
    {
        if (common::commands.contains(command))
        {
            std::cout << command << " is a shell builtin" << std::endl;
            return 0;
        }
        else
        {
            std::cout << command << ": not found" << std::endl;
            return 1;
        }
    }
}