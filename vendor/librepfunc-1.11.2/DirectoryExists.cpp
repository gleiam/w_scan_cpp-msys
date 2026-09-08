/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sys/stat.h> // stat()


bool DirectoryExists(std::string aDirectory) {
  struct stat Stat;
  bool result = stat(aDirectory.c_str(), &Stat) == 0;
  return result and (Stat.st_mode & S_IFMT) == S_IFDIR;
}

bool DirectoryExistsW(std::wstring aDirectory) {
  return DirectoryExists(WStrToStr(aDirectory));
}
