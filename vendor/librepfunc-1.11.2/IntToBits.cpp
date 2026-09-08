/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <string>    // std::string


template<class T>
std::basic_string<T> BitsT(std::intmax_t n, size_t width) {
  std::basic_string<T> s(width,(T)'0');
  size_t p = width - 1;
  for(size_t i=0; i<width; i++) {
     if (n & 1)
        s[p] = (T)'1';
     else
        s[p] = (T)'0';
     n >>= 1;
     p--;
     }
  return s;
}

std::string IntToBits(std::intmax_t n, size_t width) {
  return BitsT<char>(n, width);
}

std::wstring IntToBitsW(std::intmax_t n, size_t width) {
  return BitsT<wchar_t>(n, width);
}
