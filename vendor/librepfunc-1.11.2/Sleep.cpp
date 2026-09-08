/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <thread>    // std::this_thread{,::sleep_for()}
#include <chrono>    // std::chrono::{,milli,micro}seconds


void Sleep(size_t s) {
  std::this_thread::sleep_for(std::chrono::seconds(s));
}

void mSleep(size_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void uSleep(size_t us) {
  std::this_thread::sleep_for(std::chrono::microseconds(us));
}
