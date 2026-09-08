/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>   // std::stringstream
#include <iomanip>   // std::setfill, std::setw, std::left, std::right
#include <repfunc.h>


template<class T>
std::basic_string<T> IntToStrT(std::intmax_t n, size_t width, T fillchar, bool left) {
  std::basic_stringstream<T> ss;
  ss << std::setfill(fillchar) << std::setw(width);

  if (left)
     ss << std::left;
  else
     ss << std::right;

  ss << n;
  return ss.str();
}


std::string IntToStr(std::intmax_t n) {
  return IntToStrT<char>(n, 0, ' ', true);
}


std::string IntToStr(std::intmax_t n, size_t width, bool left) {
  return IntToStrT<char>(n, width, ' ', left);
}

std::string IntToStr(std::intmax_t n, size_t width, bool left, char fill) {
  return IntToStrT<char>(n, width, fill, left);
}

std::wstring IntToStrW(std::intmax_t n) {
  return IntToStrT<wchar_t>(n, 0, (wchar_t)' ', true);
}


std::wstring IntToStrW(std::intmax_t n, size_t width, bool left) {
  return IntToStrT<wchar_t>(n, width, (wchar_t)' ', left);
}


std::wstring IntToStrW(std::intmax_t n, size_t width, bool left, wchar_t fill) {
  return IntToStrT<wchar_t>(n, width, fill, left);
}
