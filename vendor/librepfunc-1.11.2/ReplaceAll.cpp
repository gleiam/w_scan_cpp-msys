/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

void ReplaceAll(std::string& s, const std::string& from, const std::string& to) {
  size_t p = 0, p1 = from.size(), p2 = to.size();
  if (s.size() > 0 and p1 > 0) {
     while((p = s.find(from, p)) != std::string::npos) {
        s.replace(p, p1, to);
        p += p2;
        }
     }
}
