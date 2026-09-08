/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>   // std:.stringstream
#include <iomanip>   // std::setfill, std::setw, std::right
#include <ctime>     // time_t, time(), ..
#include <repfunc.h> // include this library

std::string ISO8601Date(std::intmax_t t) {
  auto IntToStr = [](std::intmax_t n, size_t width) {
     std::stringstream ss;
     ss << std::setfill('0') << std::setw(width) << std::right << n;
     return ss.str();
     };

  time_t aTime;

  if (t == 0)
     aTime = time(nullptr);
  else
     aTime = (time_t) t;

  struct tm buf;
  struct tm* tm = localtime_r(&aTime, &buf);

  #if !defined(__MINGW32__) && !defined(__MING64__)
  std::string UTC_Offset;
  if (tm->tm_gmtoff != 0) {
     if (tm->tm_gmtoff > 0)
        UTC_Offset = "+";
     else
        UTC_Offset = "-";
     size_t HH = abs(tm->tm_gmtoff) / 3600;
     size_t MM = abs(tm->tm_gmtoff) % 3600;
     UTC_Offset += IntToStr(HH, 2) + ":" + IntToStr(MM, 2);
     }
  else
     UTC_Offset = "Z";
  #else
     /* msys2/mingw64 doesn't have tm_gmtoff */
     const char* UTC_Offset = "Z";
  #endif

  return IntToStr(1900+tm->tm_year,4) +
         '-' +
         IntToStr(1+tm->tm_mon,2) +
         '-' +
         IntToStr(tm->tm_mday,2) +
         'T' +
         IntToStr(tm->tm_hour,2) +
         ':' +
         IntToStr(tm->tm_min,2) +
         ':' +
         IntToStr(tm->tm_sec,2) +
         UTC_Offset;
}
