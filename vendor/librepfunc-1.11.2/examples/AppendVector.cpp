/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::vector<int> s{1,2,3};
  std::vector<int> t{4,5,6};

  AppendVector(s,t);

  /* print vector s */
  for(auto i:s)
     std::cout << IntToStr(i) << ',';
  std::cout << std::endl;

  return 0;
}
