/*******************************************************************************
 * librepfunc: A tiny lib of common functions and tasks in my c++ projects.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::stod
#include <iostream>  // std::cerr
#include <limits>    // std::numeric_limits
#include <repfunc.h>

/* A valid floating point number using the "C" locale is formed by
 * an optional sign character (+ or -),
 * followed by one of:
 *  - A sequence of digits, optionally containing a decimal-point character (.),
 *    optionally followed by an exponent part (an e or E character followed by
 *    an optional sign and a sequence of digits).
 *  - A 0x or 0X prefix, then a sequence of hexadecimal digits (as in isxdigit)
 *    optionally containing a period which separates the whole and fractional
 *    number parts. Optionally followed by a power of 2 exponent
 *    (a p or P character followed by an optional sign and a sequence of hexa-
 *    decimal digits).
 *  - INF or INFINITY (ignoring case).
 *  - NAN or NANsequence (ignoring case), where sequence is a sequence of char,
 *    where each character is either an alphanumeric character (as in isalnum)
 *    or the underscore character (_).
 */

/* IMPORTANT!
 * 1. Different to std::stod() and strtod(), StrToFloat silently accepts
 *    period (.) and comma (,) as decimal-separator.
 *
 * 2. StrToFloat is locale-independent.
 *
 * 3. Any lower control char is considered a whitespace and left trimmed,
 *    whereas std::stod() and strtod() trims only those as isspace knows.
 *
 * 4. StrToFloat shouldn' throw exceptions. At least, thats one goal.
 */

double StrToFloat(const std::string& s, size_t* pos) {
  size_t p, len = s.size();
  const char* P = s.c_str();
 
  // trim left any lower control chars.
  for(p=0;p<len;p++) if (P[p] > 0x20) break;

  char first = P[p];

  if (first == 0) {
     std::cerr << __FUNCTION__ << ": cannot parse '" << s << "'" << std::endl;
     if (pos) *pos = p;
     return std::numeric_limits<double>::quiet_NaN();
     }

  // optional sign character (+ or -)
  bool plus  = first == '+';
  bool minus = first == '-';
  if (plus or minus) {
     p++;
     first = P[p];
     }

  char second = len > (p+1) ? P[p+1] : 0;
  char third  = len > (p+2) ? P[p+2] : 0;

  // NAN or NANsequence
  bool nan = ((first  == 'N') or (first  == 'n')) and
             ((second == 'A') or (second == 'a')) and
             ((third  == 'N') or (third  == 'n'));
  if (nan) {
     p += 3;

     for(;p<len;) {
        char sequence = P[p];
        if ((sequence == '_') or
           ((sequence >= 'A') and (sequence <= 'Z')) or
           ((sequence >= 'a') and (sequence <= 'z')))
           p++;
        else
           break;
        }

     if (pos) *pos = p;
     return std::numeric_limits<double>::quiet_NaN();
     }


  // INF or INFINITY (ignoring case)
  bool inf = ((first  == 'I') or (first  == 'i')) and
             ((second == 'N') or (second == 'n')) and
             ((third  == 'F') or (third  == 'f'));
  if (inf) {
     p += 3;
     char c4 = len > (p+1) ? P[p+1] : 0;
     char c5 = len > (p+2) ? P[p+2] : 0;
     char c6 = len > (p+3) ? P[p+3] : 0;
     char c7 = len > (p+4) ? P[p+4] : 0;
     char c8 = len > (p+5) ? P[p+5] : 0;

     if (((c4 == 'I') or (c4  == 'i')) and
         ((c5 == 'N') or (c5  == 'n')) and
         ((c6 == 'I') or (c6  == 'i')) and
         ((c7 == 'T') or (c7  == 't')) and
         ((c8 == 'Y') or (c8  == 'y')))
        p += 5;

     if (pos) *pos = p;

     if (minus)
        return -std::numeric_limits<double>::infinity();
     else
        return  std::numeric_limits<double>::infinity();
     }


  bool hex =  (first  == '0') and
             ((second == 'X') or (second == 'x'));

  if (hex) {
  /*  - A 0x or 0X prefix, then a sequence of hexadecimal digits (as in isxdigit)
   *    optionally containing a period which separates the whole and fractional
   *    number parts. Optionally followed by a power of 2 exponent
   *    (a p or P character followed by an optional sign and a sequence of hexa-
   *    decimal digits).
   */
     p += 2; // skip prefix "0x"

     size_t whole_part = 0;
     size_t fract_part = 0;
     size_t fract_div  = 1;
     size_t exp_part   = 0;
     bool   exp_sign   = true;
     char next = 0;

     for(; p<len; p++) {
        next = P[p];
        if ((next >= '0') and (next <= '9')) {
           whole_part *= 16;
           whole_part += (next - '0');
           }
        else if ((next >= 'A') and (next <= 'F')) {
           whole_part *= 16;
           whole_part += 10 + (next - 'A');
           }
        else if ((next >= 'a') and (next <= 'f')) {
           whole_part *= 16;
           whole_part += 10 + (next - 'a');
           }
        else
           break;
        }

     if ((next == '.') or (next == ',')) {
        for(p++; p<len; p++) {
           next = P[p];
           if ((next >= '0') and (next <= '9')) {
              fract_div  *= 16;
              fract_part *= 16;
              fract_part += (next - '0');
              }
           else if ((next >= 'A') and (next <= 'F')) {
              fract_div  *= 16;
              fract_part *= 16;
              fract_part += 10 + (next - 'A');
              }
           else if ((next >= 'a') and (next <= 'f')) {
              fract_div  *= 16;
              fract_part *= 16;
              fract_part += 10 + (next - 'a');
              }
           else
              break;
          }
        }
     if ((next == 'P') or (next == 'p')) {
        p++;
        next = P[p];

        if ((next == '+') or (next == '-')) {
           exp_sign = (next == '+');
           p++;
           next = P[p];
           }

        for(; p<len; p++) {
           next = P[p];
           if ((next >= '0') and (next <= '9')) {
              exp_part *= 16;
              exp_part += (next - '0');
              }
           else if ((next >= 'A') and (next <= 'F')) {
              exp_part *= 16;
              exp_part += 10 + (next - 'A');
              }
           else if ((next >= 'a') and (next <= 'f')) {
              exp_part *= 16;
              exp_part += 10 + (next - 'a');
              }
           else
              break;
          }
        }

     double fract = (double)fract_part / (double)fract_div;
     double result = (double)whole_part + fract;
     if (minus)
        result *= -1.0;
     if (exp_part) {
        double pow = (double) (1 << exp_part);
        if (exp_sign)
           result *= pow;
        else
           result *= 1.0/pow;
        }
     if (pos) *pos = p;
     return result;
     }
  else {
  /*  - A sequence of digits, optionally containing a decimal-point character (.),
   *    optionally followed by an exponent part (an e or E character followed by
   *    an optional sign and a sequence of digits).
   */
     size_t whole_part = 0;
     size_t fract_part = 0;
     size_t fract_div  = 1;
     size_t exp_part   = 0;
     bool   exp_sign   = true;
     char next = 0;

     for(; p<len; p++) {
        next = P[p];
        if ((next < '0') or (next > '9'))
           break;
        whole_part *= 10;
        whole_part += (next - '0');
        }

     if ((next == '.') or (next == ',')) {
        for(p++; p<len; p++) {
          next = P[p];
          if ((next < '0') or (next > '9'))
             break;
          fract_div  *= 10;
          fract_part *= 10;
          fract_part += (next - '0');
          }
        }

     if ((next == 'E') or (next == 'e')) {
        p++;
        next = P[p];

        if ((next == '+') or (next == '-')) {
           exp_sign = (next == '+');
           p++;
           next = P[p];
           }

        for(; p<len; p++) {
          next = P[p];
          if ((next < '0') or (next > '9'))
             break;
          exp_part *= 10;
          exp_part += (next - '0');
          }
        }

     double fract = (double)fract_part / (double)fract_div;
     double result = (double)whole_part + fract;
     if (minus)
        result *= -1.0;
     if (exp_part) {
        size_t pow = 1;
        for(;exp_part;exp_part--) pow *= 10;
        if (exp_sign)
           result *= (double)pow;
        else
           result *= 1.0/((double)pow);
        }
     if (pos) *pos = p;
     return result;
     }


  // never reached.
  std::cerr << __FUNCTION__ << ":" << __LINE__ << ": something is wrong here.";
  return std::numeric_limits<double>::quiet_NaN();
}

double WStrToFloat(const std::wstring& ws, size_t* pos) {
  std::string s = WStrToStr(ws);
  return StrToFloat(s, pos);
}
