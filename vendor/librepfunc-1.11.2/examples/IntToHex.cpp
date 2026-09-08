/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::to_string()
#include <iostream>  // std::cout
#include <vector>    // std::vector
#include <cstdint>   // uint(8,16,32,64)_t
#include <repfunc.h> // include this library

int main() {
  // some example data..
  std::vector<uint32_t> data;

  for(size_t i=0; i<16; i++)
     data.push_back(1 << i);

  std::cout << "data = " << std::endl;
  for(auto i:data)
     std::cout << "   '" << IntToHex(i,4) << "'" << std::endl;

  return 0;
}
