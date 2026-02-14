#include <string>
#include <iostream>

namespace shell::echo
{
    int execute(const std::vector<std::string>& tokens)
    {
        for (const std::string& token : tokens)
        {
            std::printf("%s", token.c_str());
        }
        std::printf("\n");
        return 0;
    }
}