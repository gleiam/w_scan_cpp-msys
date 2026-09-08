/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::cout << "IntToBits(0xDEADBEEF,32) = '" << IntToBits(0xDEADBEEF,32) << "'" << std::endl;
  std::cout << "IntToBits(0xDEADBEEF,24) = '" << IntToBits(0xDEADBEEF,24) << "'" << std::endl;
  std::cout << "IntToBits(0xDEADBEEF,16) = '" << IntToBits(0xDEADBEEF,16) << "'" << std::endl;
  std::cout << "IntToBits(0xDEADBEEF,8)  = '" << IntToBits(0xDEADBEEF,8)  << "'" << std::endl;

  return 0;
}
