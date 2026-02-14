#include <string>
#include <unordered_set>

namespace shell::common
{
    static std::unordered_set<std::string> commands {
        "echo",
        "exit",
        "type"
    };
}