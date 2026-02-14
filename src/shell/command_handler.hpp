#pragma once

#include <common/common.hpp>

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <sstream>

namespace shell
{

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

    int16_t execute(const std::string& command)
    {
        const auto [keyword, input] = extract_keyword_input(command);
        if (!common::string_to_command.contains(keyword))
        {
            std::cout << keyword << ": command not found" << std::endl;
            return 1;
        }
        return common::string_to_command[keyword](input);
    }

    void repl()
    {
        while (true)
        {
            std::cout << "$ ";
            std::string command;
            std::getline(std::cin, command);
            int16_t exit_code = execute(command);
            if (exit_code == -1)
            {
                break;
            }
        }
    }
}