/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::string s("Hello World.");

  std::cout << "s = " << s << std::endl;
  std::cout << "UpperCase(s) = " << UpperCase(s) << std::endl;
  std::cout << "LowerCase(s) = " << LowerCase(s) << std::endl;

  return 0;
}
