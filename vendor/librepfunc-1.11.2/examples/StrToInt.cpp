/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::string s("1234");

  std::cout << "s = '" << s << "'" << std::endl;

  std::cout << "StrToInt(s) = "  << StrToInt(s) << std::endl;

  std::cout << "StrToInt(\"0x\" + s) = "
            << StrToInt("0x" + s)
            << " (hex:" << IntToHex(StrToInt("0x" + s), 4) << ')'
            << std::endl;


  return 0;
}
