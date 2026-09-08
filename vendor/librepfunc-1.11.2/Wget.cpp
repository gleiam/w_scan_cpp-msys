/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

std::string wget(std::string& Addr, std::string& Dest) {
  std::string process("wget");
  std::string message;

  process += " -O " + Dest
          + " -t 3"
          + " -nc"
          + " " + Addr;

  SystemExecute(process, message);

  return message;
}
