/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <ctime>     // time()
#include <repfunc.h> // include this library

int main() {
  std::cout << "now it's " << ISO8601Date() << std::endl;

  std::cout << "and in one hour " << ISO8601Date(time(0) + 3600) << std::endl;

  return 0;
}
