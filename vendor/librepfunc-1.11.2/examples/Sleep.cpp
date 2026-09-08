/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::to_string()
#include <iostream>  // std::cout
#include <cmath>     // the math constants used in this example
#include <repfunc.h> // include this library

int main() {
  size_t NumSeconds = 5;

  std::cout << "Sleeping this thread for " + IntToStr(NumSeconds) + " seconds." << std::endl;

  // sleep thread using STL functions
  Sleep(NumSeconds);

  std::cout << "done." << std::endl;

  return 0;
}
