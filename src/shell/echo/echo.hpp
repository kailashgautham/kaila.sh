#include <string>
#include <iostream>

namespace shell::echo
{
    int16_t execute(const std::string& command)
    {
        std::cout << command << std::endl;
        return 0;
    }
}