/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::cout << "check, if Makefile exists.. ";

  if (FileExists("Makefile"))
     std::cout << "yes";
  else
     std::cout << "no";

  std::cout << std::endl;

  return 0;
}
