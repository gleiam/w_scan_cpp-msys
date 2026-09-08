/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::string s("  \t  Hello World.  \t  ");

  std::cout << "s            = '" << s            << "'" << std::endl;
  std::cout << "LeftTrim(s)  = '" << LeftTrim(s)  << "'" << std::endl;
  std::cout << "RightTrim(s) = '" << RightTrim(s) << "'" << std::endl;
  std::cout << "Trim(s)      = '" << Trim(s)      << "'" << std::endl;

  return 0;
}
