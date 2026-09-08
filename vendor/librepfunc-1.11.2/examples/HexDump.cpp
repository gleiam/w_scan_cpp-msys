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
  std::vector<uint8_t> buf;

  for(size_t i=0; i<128; i++)
     buf.push_back(i);

  HexDump("buf", buf.data(), buf.size());

  return 0;
}
