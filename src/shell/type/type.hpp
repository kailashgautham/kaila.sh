#pragma once

#include <common/commands.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <unistd.h>

namespace shell::type
{
    static std::vector<std::string> paths;

    void setup_paths(const std::string& path)
    {
        std::stringstream ss(path);
        std::string current_path;
        while (std::getline(ss, current_path, ':'))
        {
            if (std::filesystem::exists(current_path))
            {
                paths.push_back(current_path);
            }
        }
    }

    std::string get_command_path(std::string command)
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

    int16_t execute(const std::string& command)
    {
        if (common::commands.contains(command))
        {
            std::cout << command << " is a shell builtin" << std::endl;
            return 0;
        }
        std::string program_path = get_command_path(command);

        if (!program_path.empty())
        {
            std::printf("%s is %s\n", command.c_str(), program_path.c_str());
            return 0;
        }
        else
        {
            std::cout << command << ": not found" << std::endl;
            return 1;
        }
    }
}