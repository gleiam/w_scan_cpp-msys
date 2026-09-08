/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>   // std::stringstream
#include <iomanip>   // std::setfill, std::setw, std::left, std::right
#include <repfunc.h>

bool IsAsciiFile(std::string aFileName) {
  if (not FileExists(aFileName))
     return false;

  for(auto line:ReadFile(aFileName)) {
     for(auto c:line) {
        switch(static_cast<unsigned char>(c)) {
           case 9: break;
           case 32 ... 126: break;
           default: return false;
           }
        }
     }

  return true;
}
