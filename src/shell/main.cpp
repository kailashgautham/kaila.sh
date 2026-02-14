#include <command_handler.hpp>
#include <type/type.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  const std::string PATH = std::getenv("PATH");
  shell::common::setup_paths(PATH);

  shell::repl();
}
