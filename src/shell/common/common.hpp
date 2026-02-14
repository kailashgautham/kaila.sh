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
}
