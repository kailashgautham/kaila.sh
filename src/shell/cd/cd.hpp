#include <string>
#include <iostream>
#include <filesystem>

namespace shell::cd
{
    int execute(const std::string& command)
    {
        if (std::filesystem::exists(command) && std::filesystem::is_directory(command))
        {
            std::filesystem::current_path(command);
            return 0;
        }
        else
        {
            std::printf("cd: %s: No such file or directory\n", command.c_str());
            return 1;
        }
    }
}