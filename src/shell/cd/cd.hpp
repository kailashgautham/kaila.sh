#include <string>
#include <iostream>
#include <filesystem>
#include <common/common.hpp>

namespace shell::cd
{
    int execute(const std::vector<std::string>& tokens)
    {
        if (tokens[0] == "~")
        {
            std::filesystem::current_path(common::HOME);
            return 0;
        }
        if (std::filesystem::exists(tokens[0]) && std::filesystem::is_directory(tokens[0]))
        {
            std::filesystem::current_path(tokens[0]);
            return 0;
        }
        else
        {
            std::printf("cd: %s: No such file or directory\n", tokens[0].c_str());
            return 1;
        }
    }
}