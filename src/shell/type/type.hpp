#pragma once

#include <common/common.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

namespace shell::type
{

    int execute(const std::vector<std::string>& tokens)
    {
        if (common::commands.contains(tokens[0]))
        {
            std::printf("%s is a shell builtin\n", tokens[0].c_str());
            return 0;
        }
        std::string program_path = common::get_command_path(tokens[0]);

        if (!program_path.empty())
        {
            std::printf("%s is %s\n", tokens[0].c_str(), program_path.c_str());
            return 0;
        }
        else
        {
            std::printf("%s: not found\n", tokens[0].c_str());
            return 1;
        }
    }
}