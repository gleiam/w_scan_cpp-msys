/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::to_string()
#include <iostream>  // std::cout
#include <cmath>     // the math constants used in this example
#include <repfunc.h> // include this library

int main() {
  // some example number..
  int i = M_LOG2E * 1024;

  // print i using STL function
  std::cout << "std::to_string(i) = '" << std::to_string(i) << "'" << std::endl;

  // print i using IntToStr()
  std::cout << "IntToStr(i)           = '" << IntToStr(i)           << "'" << std::endl;
  std::cout << "IntToStr(i, 8, true)  = '" << IntToStr(i, 8, true)  << "'" << std::endl;
  std::cout << "IntToStr(i, 8, false) = '" << IntToStr(i, 8, false) << "'" << std::endl;

  return 0;
}
