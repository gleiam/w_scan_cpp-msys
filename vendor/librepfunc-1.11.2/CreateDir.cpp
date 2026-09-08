/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sys/stat.h> // mkdir()


bool CreateDir(std::string aDirectory, size_t aMode) {
  #if !defined(__MINGW32__) && !defined(__MING64__)
     return mkdir(aDirectory.c_str(), aMode) == 0;
  #else
     (void) aMode;
     return mkdir(aDirectory.c_str()) == 0;
  #endif
}

bool CreateDirW(std::wstring aDirectory, size_t aMode) {
  return CreateDir(WStrToStr(aDirectory), aMode);
}
