/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sys/stat.h> // stat()


bool FileExists(std::string aFile) {
  struct stat Stat;
  return stat(aFile.c_str(), &Stat) == 0;
}

bool FileExistsW(std::wstring aFile) {
  return FileExists(WStrToStr(aFile));
}
