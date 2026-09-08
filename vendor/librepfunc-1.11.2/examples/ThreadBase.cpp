/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library



class cWorker : public ThreadBase {
protected:
  void Action(void);
public:
  cWorker(void);
  ~cWorker();
};

cWorker::cWorker(void) {
  // add something to initialize here.
}

cWorker::~cWorker() {
  // clean up after yourselves
}

void cWorker::Action(void) {
  // some child thread which does work beside main thread.
  size_t n = 0;
  while(Running()) {
     std::cout << "worker thread: " << IntToStr(n++) << std::endl;
     mSleep(100);
     }
}




int main() {
  std::cout << "main thread line " << __LINE__ << std::endl;

  cWorker* child_thread = new cWorker;
  // start the thread.
  child_thread->Start();

  Sleep(5);

  // stop the thread
  child_thread->Cancel();

  // wait until thread really finished.
  child_thread->Join();

  std::cout << "main thread line " << __LINE__ << std::endl;

  return 0;
}
