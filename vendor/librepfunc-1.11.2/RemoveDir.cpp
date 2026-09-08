/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

#if !defined(__MINGW32__) && !defined(__MING64__)
   #include <unistd.h> // rmdir()
#else
   #include <direct.h> // rmdir()
#endif


bool RemoveDir(std::string aDirectory) {
  return rmdir(aDirectory.c_str()) == 0;
}

bool RemoveDirW(std::wstring aDirectory) {
  return RemoveDir(WStrToStr(aDirectory));
}
