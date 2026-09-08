/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <utility>   // std::move, std::swap
#include <chrono>    // std::chrono::milliseconds
#include <system_error>
#include <repfunc.h>


/******************************************************************************
 * class ThreadBase
 *****************************************************************************/
ThreadBase::ThreadBase()
 : fObj(pObj.get_future()) {}


ThreadBase::ThreadBase(ThreadBase&& other)
 : pObj(std::move(other.pObj)), fObj(std::move(other.fObj)) {
  std::swap(tObj,other.tObj);
}


ThreadBase::~ThreadBase() {
  Cancel();
  Join();
}


ThreadBase& ThreadBase::operator=(ThreadBase&& other)  {
  pObj = std::move(other.pObj);
  fObj = std::move(other.fObj);
  std::swap(tObj,other.tObj);
  return *this;
}


/* returns true, if the thread in Action() may continue.
 * to be checked periodically in short intervals in Action()
 */
bool ThreadBase::Running(void) {
  static constexpr auto zero_ms = std::chrono::milliseconds(0);
  return fObj.wait_for(zero_ms) == std::future_status::timeout;
}


/* start the thread defined in Action() */
bool ThreadBase::Start(void) {
  try {
     if (tObj.joinable() and not Running()) {
        // task finished - reinitialize.
        Join();
        std::promise<void> p;
        std::future<void> f(p.get_future());
        pObj = std::move(p);
        fObj = std::move(f);
        }
     if (not tObj.joinable()) {
        std::thread t([&]() { Action(); });
        std::swap(t, tObj);
        }
     }
  catch(const std::system_error& e) { return false; }
  return true;
}


/* stop the thread defined in Action() */
void ThreadBase::Cancel(void) {
  if (Running())
     pObj.set_value();
}


/* wait until the thread defined in Action() finished */
void ThreadBase::Join(void) {
  if (tObj.joinable())
     tObj.join();
}
