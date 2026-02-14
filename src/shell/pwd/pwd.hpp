#include <string>
#include <iostream>
#include <filesystem>

namespace shell::pwd
{
    int execute(const std::vector<std::string>&)
    {
        std::printf("%s\n", std::filesystem::current_path().string().c_str());
        return 0;
    }
}