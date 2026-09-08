/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  /* s is a string, to be splitted at char ':' */
  std::string s("foo:bar:foobar");
  int n = 1;

  /* now, split s into items, delimited by ':' and
   * report each item on separate line.
   * Note: using range based loop here.
   */
  for(auto item:SplitStr(s, ':'))
     std::cout << "item #" + IntToStr(n++) + " = '" << item << "'" << std::endl;

  return 0;
}
