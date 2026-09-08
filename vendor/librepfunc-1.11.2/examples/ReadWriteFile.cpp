/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout, std::cerr
#include <sstream>   // std::stringstream
#include <repfunc.h> // include this library

int main() {
  std::stringstream ss;
  std::string fname("test.txt");

  for(int i=0; i<3; i++)
     ss << "line " << IntToStr(i) << std::endl;

  /* write stream into file. */
  if (not WriteStreamToFile(fname, ss))
     std::cerr << "could not write to " << fname << std::endl;

  std::cout << "contents of " << fname << std::endl;
  for(auto str:ReadFile("test.txt"))
     std::cout << str << std::endl;

  return 0;
}
