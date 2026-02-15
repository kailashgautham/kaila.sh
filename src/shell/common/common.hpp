#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <unistd.h>

namespace shell::common
{
    static std::unordered_set<std::string> commands {
            "cd",
            "echo",
            "exit",
            "pwd",
            "type"
    };

    static std::vector<std::string> paths;

    static std::string HOME = std::getenv("HOME");
    const std::string PATH = std::getenv("PATH");

    void setup_paths()
    {
        std::stringstream ss(PATH);
        std::string current_path;
        while (std::getline(ss, current_path, ':'))
        {
            if (std::filesystem::exists(current_path))
            {
                paths.push_back(current_path);
            }
        }
    }

    std::string get_command_path(const std::string& command)
    {
        for (const std::string& path : paths)
        {
            const std::string filepath = path + "/" + command;
            if (std::filesystem::exists(filepath)
                && std::filesystem::is_regular_file(filepath)
                && access(filepath.c_str(), X_OK) == 0)
            {
                return filepath;
            }
        }
        return "";
    }

    void tokenize_apostrophe(size_t& idx, const std::string& input, std::vector<std::string>& tokenized_input)
    {
        size_t string_end = input.find(input[idx], idx + 1);
        if (string_end > idx + 1)
        {
            tokenized_input.emplace_back(input.substr(idx + 1, string_end - idx - 1));
        }
        idx = string_end + 1;
    }

    void tokenize_quote(size_t& idx, const std::string& input, std::vector<std::string>& tokenized_input)
    {
        ++idx;
        size_t string_end = input.find('\"', idx);
        for (size_t string_backslash = input.find('\\', idx);
             string_backslash != std::string::npos && string_backslash < string_end;
             string_backslash = input.find('\\', idx))
        {
            tokenized_input.emplace_back(input.substr(idx, string_backslash - idx));
            idx = string_backslash;
            if (input[idx + 1] == '\"' || input[idx + 1] == '\\')
            {
                tokenized_input.emplace_back(std::string{input[++idx]});
                if (input[idx] == '\"')
                {
                    string_end = input.find('\"', idx + 1);
                }
            }
            else
            {
                tokenized_input.emplace_back(std::string{input[idx]});
            }
            idx++;
        }
        tokenized_input.emplace_back(input.substr(idx, string_end - idx));
        idx = string_end + 1;
    }

    std::string tokenize_quoted_command(const std::string& command)
    {
        size_t idx = 0;
        std::vector<std::string> tokens;
        if (command[0] == '\'')
        {
            common::tokenize_apostrophe(idx, command, tokens);
        }
        else
        {
            common::tokenize_quote(idx, command, tokens);
        }
        std::string new_command = "";
        for (const std::string& token : tokens)
        {
            new_command += token;
        }
        return new_command;
    }

    std::vector<std::string> tokenize_input(const std::string& input)
    {
        size_t idx = 0;
        std::vector<std::string> tokenized_input;
        for (; idx < input.size(); )
        {
           if (input[idx] == '\'')
           {
               tokenize_apostrophe(idx, input, tokenized_input);
           }
           else if (input[idx] == '\"')
           {
               tokenize_quote(idx, input, tokenized_input);
           }
           else if (input[idx] == '\\')
           {
               tokenized_input.emplace_back(std::string{input[idx + 1]});
               idx += 2;
           }
           else if (input[idx] == ' ')
           {
               if (!tokenized_input.empty() && tokenized_input.back() != " ")
               {
                   tokenized_input.emplace_back(" ");
               }
               ++idx;
           }
           else
           {
               size_t string_space = input.find(' ', idx);
               size_t string_apostrophe = input.find('\'', idx);
               size_t string_quote = input.find('\"', idx);
               size_t string_backslash = input.find('\\', idx);

               if (string_space == std::string::npos && string_apostrophe == std::string::npos && string_quote == std::string::npos && string_backslash == std::string::npos)
               {
                   tokenized_input.emplace_back(input.substr(idx));
                   break;
               }

               size_t string_end = std::min({string_space, string_apostrophe, string_quote, string_backslash});
               tokenized_input.emplace_back(input.substr(idx, string_end - idx));
               idx = string_end;
           }
        }
        return tokenized_input;
    }

    std::pair<std::string, std::vector<std::string>> extract_keyword_input(const std::string& command)
    {
        size_t first_word_idx = command.find(' ');
        if (first_word_idx == std::string::npos || command[0] == '\'' || command[0] == '\"')
        {
            return {command, {}};
        }
        const std::string keyword = command.substr(0, first_word_idx);
        const std::string input = command.substr(first_word_idx + 1);
        const std::vector<std::string> tokenized_input = tokenize_input(input);
        return {keyword, tokenized_input};
    }
}
