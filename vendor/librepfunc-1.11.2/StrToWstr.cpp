/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <clocale>    // std::setlocale
#include <cstdlib>    // std::wcstombs, std::mbstowcs

/* 20251210: replace deprecated std::codecvt_utf8 with
 *           std::wcstombs, std::mbstowcs
 * https://en.cppreference.com/w/cpp/string/multibyte/mbstowcs.html
 * https://en.cppreference.com/w/cpp/string/multibyte/wcstombs.html
 */

std::string WStrToStr(std::wstring ws) {
  if (ws.empty())
     return "";
  auto* wstr = (const wchar_t*) ws.c_str();
  char mbstr[256];
  std::wcstombs(mbstr, wstr, sizeof(mbstr));
  return (const char*) mbstr;
}

std::wstring StrToWStr(std::string s) {
  if (s.empty())
     return L"";
  auto* mbstr = s.c_str();
  wchar_t wstr[256];
  std::mbstowcs(wstr, mbstr, sizeof(wstr)/sizeof(wstr[0]));
  return (const wchar_t*) wstr;
}
