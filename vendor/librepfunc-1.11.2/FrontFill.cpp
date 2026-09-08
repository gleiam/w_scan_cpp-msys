/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>


template<class T>
std::basic_string<T> FrontFillT(std::basic_string<T> s, size_t n) {
  ssize_t missing = n - s.size();
  if (missing > 0)
     return std::basic_string<T>(missing, (T)' ') + s;
  return s;
}


template<class T>
std::basic_string<T> BackFillT(std::basic_string<T> s, size_t n) {
  ssize_t chars = s.size();

  /* For UTF-8 encoded chars, the number of bytes is larger than the
   * number of chars. Take it into account.
   */
  for(auto c:s) {
     if (((unsigned) c & 0xE0) == 0xC0) {
        /* two byte utf8 */
        chars += -1;
        }
     else if (((unsigned) c & 0xF0) == 0xE0) {
        /* three byte utf8 */
        chars += -2;
        }
     else if (((unsigned) c & 0xF8) == 0xF0) {
        /* four byte utf8 */
        chars += -3;
        }
     }

  ssize_t missing = n - chars;

  if (missing > 0)
     return s + std::basic_string<T>(missing, (T)' ');
  return s;
}


std::string FrontFill(std::string s, size_t n) {
  return FrontFillT(s, n);
}


std::string BackFill(std::string s, size_t n) {
  return BackFillT(s, n);
}


std::wstring FrontFillW(std::wstring s, size_t n) {
  return FrontFillT(s, n);
}


std::wstring BackFillW(std::wstring s, size_t n) {
  return BackFillT(s, n);
}
