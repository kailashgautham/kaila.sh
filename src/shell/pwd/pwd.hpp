#include <string>
#include <iostream>
#include <filesystem>

namespace shell::pwd
{
    int execute(const std::string&)
    {
        std::cout << std::filesystem::current_path().string() << std::endl;
        return 0;
    }
}