#pragma once

#include <common/common.hpp>
#include <echo/echo.hpp>
#include <exit/exit.hpp>
#include <type/type.hpp>

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <sstream>

namespace shell
{
    static std::unordered_map<std::string, std::function<int (const std::string&)>> string_to_command {
            {"echo", &echo::execute},
            {"exit", &exit::execute},
            {"type", &type::execute},
    };

    std::pair<std::string, std::string> extract_keyword_input(const std::string& command)
    {
        size_t first_word_idx = command.find(' ');
        if (first_word_idx == std::string::npos)
        {
            return {command, ""};
        }
        const std::string keyword = command.substr(0, first_word_idx);
        const std::string input = command.substr(first_word_idx + 1);
        return {keyword, input};
    }

    int execute(const std::string& command)
    {
        const auto [keyword, input] = extract_keyword_input(command);
        if (string_to_command.contains(keyword))
        {
            return string_to_command[keyword](input);
        }
        else if (!common::get_command_path(keyword).empty())
        {
            return std::system(command.c_str());
        }
        else
        {
            std::cout << keyword << ": command not found" << std::endl;
            return 1;
        }
    }

    void repl()
    {
        while (true)
        {
            std::cout << "$ ";
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