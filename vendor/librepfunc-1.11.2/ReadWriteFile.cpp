/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <sstream>   // std::stringstream
#include <fstream>   // std::ifstream
#include <repfunc.h>

std::stringstream ReadFileToStream(std::string aFileName) {
  std::stringstream ss;
  std::ifstream is(aFileName.c_str());
  if (is) {
     ss << is.rdbuf();
     is.close();
     }
  return ss; 
}

bool WriteStreamToFile(std::string aFileName, std::stringstream& ss) {
  std::ofstream os(aFileName.c_str());
  if (os.fail())
     return false;

  os << ss.rdbuf();
  bool result = os.good();
  os.close();
  return result;
}

std::vector<std::string> ReadFile(std::string aFileName, bool empty) {
  std::stringstream ss = ReadFileToStream(aFileName);
  std::string s;
  std::vector<std::string> result;

  while(std::getline(ss, s)) {
     if (not empty and s.empty())
        continue;
     result.push_back(s);
     }
  return result;
}

bool WriteFile(std::string aFileName, std::vector<std::string>& lines) {
  std::ofstream os(aFileName.c_str());
  if (os.fail())
     return false;

  for(const auto& s:lines)
     os << s << std::endl;
  bool result = os.good();
  os.close();
  return result;
}
