#include <string>
#include <iostream>

namespace shell::echo
{
    int execute(const std::string& command)
    {
        std::printf("%s\n", command.c_str());
        return 0;
    }
}