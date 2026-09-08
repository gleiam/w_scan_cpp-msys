/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <array>       // std::array
#include <repfunc.h>


std::string B64tbl("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "abcdefghijklmnopqrstuvwxyz"
                   "0123456789+/");


std::array<uint8_t,4> get4x6(std::array<uint8_t,3> bytes) {
  std::array<uint8_t,4> result;

  result[0] = bytes[0] >> 2;
  result[1] = ((bytes[0] & 3 ) << 4) | (bytes[1] >> 4);
  result[2] = ((bytes[1] & 15) << 2) | (bytes[2] >> 6);
  result[3] = bytes[2] & 0x3F;

  return result;
}


std::array<uint8_t,3> get3x8(std::array<uint8_t,4> sx) {
  std::array<uint8_t,3> result;

  result[0] = (sx[0] << 2) | (sx[1] >> 4);
  result[1] = ((sx[1] & 15) << 4) | ((sx[2] & 0x3C) >> 2);
  result[2] = ((sx[2] & 3 ) << 6) | sx[3];

  return result;
}


uint8_t getIdx(char c, std::string& alphabet) {
  if (c == '=')
     return 0;
  return alphabet.find(c);
}


std::string ToBase64(std::vector<uint8_t>& bytes, std::string& alphabet) {
  std::string result;
  result.reserve((4*(bytes.size()+1))/3);

  size_t len = bytes.size();
  const uint8_t* buf = bytes.data();
  while(len > 2) {
     auto sx = get4x6({buf[0],buf[1],buf[2]});
     result += alphabet[sx[0]];
     result += alphabet[sx[1]];
     result += alphabet[sx[2]];
     result += alphabet[sx[3]];
     len -= 3;
     buf += 3;
     }

  if (len == 2) {
     auto sx = get4x6({buf[0],buf[1],0});
     result += alphabet[sx[0]];
     result += alphabet[sx[1]];
     result += alphabet[sx[2]];
     result += "=";
     }
  else if (len == 1) {
     auto sx = get4x6({buf[0],0,0});
     result += alphabet[sx[0]];
     result += alphabet[sx[1]];
     result += "==";
     }
  return result;
}


std::string ToBase64(std::vector<uint8_t>& bytes) {
  return ToBase64(bytes, B64tbl);
}


std::vector<uint8_t> FromBase64(std::string s, std::string& alphabet) {
  std::vector<uint8_t> result;
  result.reserve((3*(s.size()+1))/4);

  size_t len = s.size();
  const char* c = s.c_str();
  while(len > 3) {
     auto bytes = get3x8({getIdx(c[0],alphabet),
                          getIdx(c[1],alphabet),
                          getIdx(c[2],alphabet),
                          getIdx(c[3],alphabet)});
     result.push_back(bytes[0]);
     result.push_back(bytes[1]);
     result.push_back(bytes[2]);
     if (c[3] == '=') {
        result.pop_back();
        if (c[2] == '=')
           result.pop_back();
        break;
        }
     len -= 4;
     c += 4;
     }

  if (len == 3) {
     auto bytes = get3x8({getIdx(c[0],alphabet),
                          getIdx(c[1],alphabet),
                          getIdx(c[2],alphabet),
                          0});
     result.push_back(bytes[0]);
     result.push_back(bytes[1]);
     }
  else if (len == 2) {
     auto bytes = get3x8({getIdx(c[0],alphabet),
                          getIdx(c[1],alphabet),
                          0,0});
     result.push_back(bytes[0]);
     }
  return result;
}


std::vector<uint8_t> FromBase64(std::string s) {
  return FromBase64(s, B64tbl);
}
