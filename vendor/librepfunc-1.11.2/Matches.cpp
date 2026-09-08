/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>

bool Matches(std::string String, std::string Pattern) {
  if (Pattern == "*") return true;

  const char* string  = String.c_str();
  const char* pattern = Pattern.c_str();
  bool result = true;

  while(true) {
     switch(pattern[0]) {
        case 0:
           /* end of Pattern */
           return (string[0] == 0);
        case '*': {
           if (pattern[1] == 0) {
              /* pattern ends with a '*' and matches everything now,
               * stop searching. */
              return true;
              }
           else
              pattern++;

           while(*string) {
              if (Matches(string,pattern)) return true;
              string++;
              }
           }
           break;
        case '?': {
           if (string[0] == 0) {
              /* Pattern requested a single arbitrary char here,
               * but our String is too short */
              return false;
              }
           string++;  /* still a match - move to next char */
           pattern++; /* still a match - move to next char */
           }
           break;
        case '[': {
           if (pattern[1] == 0 or    /* missing closing backet ']' in Pattern         */
               pattern[1] == '[' or  /* nested sequence or by mistace '[' in Pattern  */
               pattern[1] == ']')    /* closed barcket without any sequence of chars. */
              return false;

           if (pattern[1] == '^') {  /* we want to exclude one or more chars */
              pattern += 2;          /* move to char after "[^"              */
              while(pattern[0] != ']') {
                 if (pattern[1] == '-') { /* a range of chars is to be excluded */
                    if (string[0] >= pattern[0] and /* actual char in String begins after begin of excluded range */
                        string[0] <= pattern[2])    /* actual char in String ends  before end of excluded range   */
                       /* actual char is in excluded range */
                       return false;
                    else
                       /* still a match, skip range in Pattern */
                       pattern += 3;
                    }
                 else {
                    if (string[0] == pattern[0])
                       /* we found exactly the excluded char -> no match */
                       return false;
                    else
                       /* still a match, continue */
                       pattern++;
                    }
                 }
              } /* end '^' */
           else {         /* we want to include one or more chars */
              pattern++;  /* next char is after the '['           */
              result = false;
              while(pattern[0] != ']') {
                 if (pattern[1] == '-') { /* a range of chars is to be included */
                    if (string[0] >= pattern[0] and /* actual char in String begins after begin of included range */
                        string[0] <= pattern[2]) {  /* actual char in String ends before end of included range    */
                       /* actual char is in included range */
                       result = true;
                       break;
                       }
                    else
                       /* result is already false. But - couldn't we return false here ? */
                       pattern += 3;
                    }
                 else {
                    if (string[0] == pattern[0]) {
                       /* we found exactly the included char */
                       result = true;
                       break;
                       }
                    else
                       /* result is already false. But - couldn't we return false here ? */
                       pattern++;
                    }
                 }
              }

           if (!result) return false;
           while(pattern[0] and pattern[0] != ']') pattern++;
           if (! pattern[0]) return false;
           string++;
           pattern++;
           }
           break;
        default:
           if (string[0] != pattern[0]) { /* compare two single characters. */
              return false;
              }
           string++;
           pattern++;
        }
     }
}
