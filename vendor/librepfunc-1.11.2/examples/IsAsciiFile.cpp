/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>
#include <repfunc.h>


int main(int argc, char** argv) {

  if (argc < 2) {
     std::cerr << "Please provide a file in command line." << std::endl;
     return -1;
     }

  if (IsAsciiFile(argv[1]))
     std::cout << argv[1] << " is an ASCII file." << std::endl;
  else
     std::cout << argv[1] << " is not an ASCII file." << std::endl;

  return 0;
}
