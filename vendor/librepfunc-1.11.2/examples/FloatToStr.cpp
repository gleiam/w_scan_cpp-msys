/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::to_string()
#include <iostream>  // std::cout
#include <cmath>     // the math constants used in this example
#include <repfunc.h> // include this library

int main() {
  // some example value with large number of digits..
  double d = pow(M_E, M_PI);

  // print d using STL function
  std::cout << "std::to_string(d) = '" << std::to_string(d) << "'" << std::endl;

  // print d using FloatToStr()
  std::cout << "FloatToStr(d)              = '" << FloatToStr(d)              << "'" << std::endl;
  std::cout << "FloatToStr(d, 8, 2, true)  = '" << FloatToStr(d, 8, 2, true)  << "'" << std::endl;
  std::cout << "FloatToStr(d, 8, 2, false) = '" << FloatToStr(d, 8, 2, false) << "'" << std::endl;
  std::cout << "FloatToStr(d, 0, 10, true) = '" << FloatToStr(d, 0, 10, true) << "'" << std::endl;
  std::cout << "ExpToStr(d, 2)             = '" << ExpToStr(d, 2)             << "'" << std::endl;

  return 0;
}
