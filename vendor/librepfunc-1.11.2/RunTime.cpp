/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

void cRunTime::Start(void) {
  t1 = std::chrono::high_resolution_clock::now();
}

void cRunTime::Stop(void) {
  t2 = std::chrono::high_resolution_clock::now();
}

double cRunTime::MilliSeconds(void) {
  std::chrono::duration<double, std::milli> msecs = t2 - t1;
  return msecs.count();
}

double cRunTime::MicroSeconds(void) {
  std::chrono::duration<double, std::micro> usecs = t2 - t1;
  return usecs.count();
}
