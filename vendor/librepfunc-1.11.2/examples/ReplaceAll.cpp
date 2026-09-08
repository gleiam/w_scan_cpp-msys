/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::string s("abc def ghi abc def ghi");
  ReplaceAll(s, "abc", "xyz");
  std::cout << "s = " << s << std::endl;

  return 0;
}
