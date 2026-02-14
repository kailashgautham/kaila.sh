#include <iostream>
#include <command_handler.hpp>

int main()
{
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

   shell::repl();
}
