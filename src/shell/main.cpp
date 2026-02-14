#include <command_handler.hpp>
#include <type/type.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  shell::common::setup_paths();

  shell::repl();
}
