/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>   // std:.stringstream
#include <iomanip>   // std::setfill, std::setw, std::right
#include <ctime>     // time_t, time(), ..
#include <repfunc.h> // include this library

std::string TimeStr(std::intmax_t t) {
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

  return IntToStr(tm->tm_mday,2) +
         '.' +
         IntToStr(1+tm->tm_mon,2) +
         '.' +
         IntToStr(1900+tm->tm_year,4) +
         ' ' +
         IntToStr(tm->tm_hour,2) +
         ':' +
         IntToStr(tm->tm_min,2) +
         ':' +
         IntToStr(tm->tm_sec,2);
}
