/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sstream>   // std::stringstream
#include <iomanip>   // std::uppercase, std::setfill, std::setw


template<class T>
std::basic_string<T> OctT(std::intmax_t n, size_t width) {
  std::basic_stringstream<T> ss;
  ss << std::uppercase << std::setfill((T)'0') << std::setw(width) << std::oct << n;
  return ss.str();
}

std::string IntToOct(std::intmax_t n, size_t width) {
  return OctT<char>(n, width);
}

std::wstring IntToOctW(std::intmax_t n, size_t width) {
  return OctT<wchar_t>(n, width);
}
