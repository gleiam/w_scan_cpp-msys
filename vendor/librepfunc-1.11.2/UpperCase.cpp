/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <algorithm>

typedef int (*UnaryOperation)(int ch);

template<class T>
std::basic_string<T> CaseT(std::basic_string<T> s, UnaryOperation conv) {
  std::basic_string<T> r(s);
  std::transform(r.begin(), r.end(), r.begin(), conv);
  return r;
}


std::string LowerCase(std::string s) {
  return CaseT(s, ::tolower);
}

std::string UpperCase(std::string s) {
  return CaseT(s, ::toupper);
}

std::wstring LowerCase(std::wstring s) {
  return CaseT(s, ::tolower);
}

std::wstring UpperCase(std::wstring s) {
  return CaseT(s, ::toupper);
}
