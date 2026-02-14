#include <string>
#include <iostream>

namespace shell::echo
{
    int execute(const std::string& command)
    {
        std::cout << command << std::endl;
        return 0;
    }
}