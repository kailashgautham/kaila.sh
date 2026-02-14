#pragma once

#include <common/common.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

namespace shell::type
{

    int execute(const std::string& command)
    {
        if (common::commands.contains(command))
        {
            std::cout << command << " is a shell builtin" << std::endl;
            return 0;
        }
        std::string program_path = common::get_command_path(command);

        if (!program_path.empty())
        {
            std::printf("%s is %s\n", command.c_str(), program_path.c_str());
            return 0;
        }
        else
        {
            std::cout << command << ": not found" << std::endl;
            return 1;
        }
    }
}