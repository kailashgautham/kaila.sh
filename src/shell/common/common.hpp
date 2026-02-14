#pragma once

#include <echo/echo.hpp>
#include <exit/exit.hpp>
#include <type/type.hpp>

#include <functional>
#include <string>
#include <unordered_map>

namespace shell::common
{
    static std::unordered_map<std::string, std::function<int16_t (const std::string&)>> string_to_command {
            {"echo", &echo::execute},
            {"exit", &exit::execute},
            {"type", &type::execute},
    };
}
