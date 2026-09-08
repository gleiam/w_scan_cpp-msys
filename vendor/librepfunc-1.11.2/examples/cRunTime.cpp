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

  /* measure the time SplitStr() needs, including the time for printing
   * to stdout (which is sloooow).
   */
  cRunTime runtime;

  runtime.Start();
  for(auto item:SplitStr(s, ':'))
     std::cout << "item #" + IntToStr(n++) + " = '" << item << "'" << std::endl;
  runtime.Stop();

  std::cout << "SplitStr() took "
            << FloatToStr(runtime.MilliSeconds()) 
            << " msecs, including std::cout for print to stdout."
            << std::endl;

  return 0;
}
