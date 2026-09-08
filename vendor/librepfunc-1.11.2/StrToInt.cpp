/*******************************************************************************
 * librepfunc: A tiny lib of common functions and tasks in my c++ projects.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::stoll
#include <iostream>  // std::cerr
#include <exception> // std::exception
#define __STDC_LIMIT_MACROS
#include <cmath>     // INTMAX_MAX
#include <repfunc.h>

template<class T>
std::intmax_t StrToIntT(const std::basic_string<T>& s, size_t* pos, size_t base, const char* f) {
  constexpr std::intmax_t err = INTMAX_MAX; /* greater or equal 2^63 - 1 */

  if (s.empty()) {
     std::cerr << f
               << ": ERROR: cannot convert empty string to integer."
               << std::endl;
     return err;
     }
  else if ((base == 1) or (base > 36)) {
     std::cerr << f
               << ": ERROR: invalid base: " + IntToStr(base)
               << std::endl;
     return err;
     }
  else {
     try {
        return std::stoll(s, pos, base);
        }
     catch(const std::exception& e) {
        std::cerr << f
               << ": ERROR: cannot convert to integer: "
               << e.what() << std::endl;
        return err;
        }
     }
}

std::intmax_t StrToInt(const std::string& s, size_t* pos, size_t base) {
  return StrToIntT(s, pos, base, __PRETTY_FUNCTION__);
}

std::intmax_t WStrToInt(const std::wstring& s, size_t* pos, size_t base) {
  return StrToIntT(s, pos, base, __PRETTY_FUNCTION__);
}
