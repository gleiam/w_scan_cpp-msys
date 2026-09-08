/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::cout << "list all cpp files.. " << std::endl;

  for(auto s:cFileList("./", ".cpp").List())
     std::cout << "   " << s << std::endl;

  return 0;
}
