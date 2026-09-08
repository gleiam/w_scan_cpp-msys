/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sstream>   // std::stringstream
#include <iomanip>   // std::uppercase, std::setfill, std::setw


template<class T>
std::basic_string<T> HexT(std::intmax_t n, size_t width) {
  std::basic_stringstream<T> ss;
  ss << std::uppercase << std::setfill((T)'0') << std::setw(width) << std::hex << n;
  return ss.str();
}

std::string IntToHex(std::intmax_t n, size_t width) {
  return "0x" + HexT<char>(n, width);
}

std::wstring IntToHexW(std::intmax_t n, size_t width) {
  return L"0x" + HexT<wchar_t>(n, width);
}
