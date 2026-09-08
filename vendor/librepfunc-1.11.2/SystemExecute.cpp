/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <array>  // std::array
#include <cstdio> // popen(), feof(), fread()


int SystemExecute(const std::string& process, std::string& message) {
  auto f = popen(process.c_str(), "r");
  if (f == nullptr) {
     message = "Cannot open pipe.";
     return -1;
     }

  std::array<char, 256> buffer;
  size_t bytes;
  while(not std::feof(f)) {
     bytes = std::fread(buffer.data(), 1, buffer.size(), f);
     message.append(buffer.data(), bytes);
     }

  return pclose(f);
}
