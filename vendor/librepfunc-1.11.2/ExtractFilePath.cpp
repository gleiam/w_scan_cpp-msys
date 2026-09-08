/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>


std::string ExtractFilePath(std::string aFile) {
  auto p = aFile.find_last_of("/\\");
  if (p != std::string::npos) {
     aFile.erase(p+1, aFile.size());
     }
  return aFile;
}

std::wstring ExtractFilePathW(std::wstring aFile) {
  auto p = aFile.find_last_of(L"/\\");
  if (p != std::string::npos) {
     aFile.erase(p+1, aFile.size());
     }
  return aFile;
}
