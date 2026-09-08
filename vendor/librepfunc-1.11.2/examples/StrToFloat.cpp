/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <vector>    // std::vector
#include <iostream>  // std::cout
#include <chrono>
#include <repfunc.h> // include this library


int main() {
  std::vector<std::string> tests = {
    "3",
    "-3",
    " 3",
    " -3",    
    "     34",
    "     34.3",
    "     34,3",
   "    -34",
    "    -34.3",
    "    -34,3",
    "     34e12",
    "     34.3e12",
    "     34,3e12",
    "     34E12",
    "     34.3E12",
    "     34,3E12",
    "    -34e12",
    "    -34.3e12",
    "    -34,3e12",
    "    -34E12",
    "    -34.3E12",
    "    -34,3E12",
    "     34e-12",
    "     34.3e-12",
    "     34,3e-12",
    "     34E-12",
    "     34.3E-12",
    "     34,3E-12",
    "    -34e-12",
    "    -34.3e-12",
    "    -34,3e-12",
    "    -34E-12",
    "    -34.3E-12",
    "    -34,3E-12",
    "12abc",
    "   0x1.fp3", // 1 15/16 * 2^3 ==  1.9375 * 8 == 1.55e1
  };

  std::cout << "This example shows the different behaviour of \n"
            << "StrToFloat vs std::stod - compare the results." << std::endl;


  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2,t3,t4;
  duration<double, std::milli> msecs1, msecs2;
  size_t p;
 
  t1 = std::chrono::high_resolution_clock::now();
  for(auto s:tests) {
     std::cout << "StrToFloat('" << s << "', &p) = (" << StrToFloat(s, &p) << "," << (int)p << ")" << std::endl;     
     }
  t2 = std::chrono::high_resolution_clock::now();



  t3 = std::chrono::high_resolution_clock::now();
  for(auto s:tests) {
     std::cout << "std::stod ('" << s << "', &p) = (" << std::stod(s, &p) << "," << (int)p << ")" << std::endl;     
     }
  t4 = std::chrono::high_resolution_clock::now();

  msecs1 = t2 - t1;
  msecs2 = t4 - t3;

  std::cout << "StrToFloat took " << msecs1.count() << "msec" << std::endl;
  std::cout << "std::stod took  " << msecs2.count() << "msec" << std::endl;

  return 0;
}

