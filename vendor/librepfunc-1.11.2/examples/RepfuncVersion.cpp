/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::cout << "librepfunc version = \'"
            << RepfuncVersion()
            << "\'" << std::endl;

  return 0;
}
