/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

std::intmax_t BCDtoDecimal(std::intmax_t bcd) {
  std::intmax_t result = 0;
  for(std::intmax_t scale=1; bcd; scale*=10,bcd>>=4)
     result += scale * (bcd & 15);
  return result;
}
