#pragma once

#include <unordered_set>
#include <string>

namespace shell
{
    void update();
    void repl();

    static constexpr std::string EXIT_COMMAND = "exit";
}