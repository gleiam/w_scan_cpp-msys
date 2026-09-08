/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <algorithm> // std::find_if()
#include <cctype>    // std::isspace()


/* std::isspace is overloaded - this is the only reason for IsSpace().
 * I could also use a lambda, but we need it twice anyway.
 */
bool IsSpace(unsigned char c) {
  return std::isspace(c);
}


template<class T>
std::basic_string<T> LeftTrimT(std::basic_string<T> s) {
  s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), IsSpace));
  return s;
}


template<class T>
std::basic_string<T> RightTrimT(std::basic_string<T> s) {
  s.erase(std::find_if_not(s.rbegin(), s.rend(), IsSpace).base(), s.end());
  return s;
}


template<class T>
std::basic_string<T> TrimT(std::basic_string<T> s) {
  return RightTrimT<T>(LeftTrimT<T>(s));
}


std::string LeftTrim(std::string s) {
  return LeftTrimT(s);
}


std::string RightTrim(std::string s) {
  return RightTrimT(s);
}


std::string Trim(std::string s) {
  return TrimT(s);
}


std::wstring LeftTrimW(std::wstring s) {
  return LeftTrimT(s);
}


std::wstring RightTrimW(std::wstring s) {
  return RightTrimT(s);
}


std::wstring TrimW(std::wstring s) {
  return TrimT(s);
}
