/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>    // std::stringstream
#include <repfunc.h>

template<class T>
std::vector<std::basic_string<T>> SplitStrT(const std::basic_string<T> s, const T delim) {
  std::basic_stringstream<T> ss(s);
  std::vector<std::basic_string<T>> result;
  std::basic_string<T> t;
  while(std::getline(ss, t, delim))
     result.push_back(t);
  return result;
}


std::vector<std::string> SplitStr(const std::string s, const char delim) {
  return SplitStrT(s, delim);
}

std::vector<std::wstring> SplitStrW(const std::wstring s, const wchar_t delim) {
  return SplitStrT(s, delim);
}
