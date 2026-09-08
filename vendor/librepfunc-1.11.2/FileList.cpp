/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <dirent.h>    // readdir(), DIR, struct dirent
#include <repfunc.h>


cFileList::cFileList(std::string aDirectory, std::string Filter) {
  for(DIR* dirp = opendir(aDirectory.c_str()); dirp; ) {
     struct dirent* d = readdir(dirp);

     if (d != nullptr) {
        std::string name(d->d_name);
        if (Filter.empty() or (name.find(Filter) != std::string::npos))
           priv.push_back(name);
        }
     else {
        closedir(dirp);
        dirp = nullptr;
        }
     }
}


std::vector<std::string> cFileList::List(void) {
  return priv;
}
