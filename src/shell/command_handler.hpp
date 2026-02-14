#pragma once

#include <cd/cd.hpp>
#include <common/common.hpp>
#include <echo/echo.hpp>
#include <exit/exit.hpp>
#include <pwd/pwd.hpp>
#include <type/type.hpp>

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <sstream>

namespace shell
{
    static std::unordered_map<std::string, std::function<int (const std::vector<std::string>&)>> string_to_command {
            {"cd", &cd::execute},
            {"echo", &echo::execute},
            {"exit", &exit::execute},
            {"pwd", &pwd::execute},
            {"type", &type::execute},
    };

    int execute(const std::string& command)
    {
        const auto [keyword, tokenized_input] = common::extract_keyword_input(command);
        if (string_to_command.contains(keyword))
        {
            return string_to_command[keyword](tokenized_input);
        }
        else if (!common::get_command_path(keyword).empty())
        {
            return std::system(command.c_str());
        }
        else
        {
            std::printf("%s: command not found\n", keyword.c_str());
            return 1;
        }
    }

    void repl()
    {
        while (true)
        {
            std::printf("$ ");
            std::string command;
            std::getline(std::cin, command);
            int exit_code = execute(command);
            if (exit_code == -1)
            {
                break;
            }
        }
    }
}