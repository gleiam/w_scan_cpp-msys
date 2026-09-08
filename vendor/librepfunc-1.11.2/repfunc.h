/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#pragma once
#include <string>  // std::string, size_t
#include <vector>  // std::vector
#include <cstdint> // std::intmax_t
#include <thread>  // std::thread
#include <future>  // std::future, std::promise
#include <chrono>  // std::chrono



/*******************************************************************************
 * Convert strings to uppercase or lowercase.
 ******************************************************************************/
std::string LowerCase(std::string s);
std::string UpperCase(std::string s);
std::wstring LowerCase(std::wstring s);
std::wstring UpperCase(std::wstring s);



/*******************************************************************************
 * Trim strings, left, right, or, both ends.
 * For details on trimmed chars, pls refer to std::isspace() from <cctype>
 ******************************************************************************/
std::string LeftTrim(std::string s);
std::string RightTrim(std::string s);
std::string Trim(std::string s);
std::wstring LeftTrimW(std::wstring s);
std::wstring RightTrimW(std::wstring s);
std::wstring TrimW(std::wstring s);



/*******************************************************************************
 * Fill up a string with spaces to be at least n chars; the opposite of Trim.
 ******************************************************************************/
std::string FrontFill(std::string s, size_t n);
std::string BackFill(std::string s, size_t n);
std::wstring FrontFillW(std::wstring s, size_t n);
std::wstring BackFillW(std::wstring s, size_t n);



/*******************************************************************************
 * splits a string on a delimiter char, and returns a vector of strings
 * from it.
 *   s         - string to split
 *   delim     - the delimiting char
 ******************************************************************************/
std::vector<std::string> SplitStr(const std::string s, const char delim);
std::vector<std::wstring> SplitStrW(const std::wstring s, const wchar_t delim);



/*******************************************************************************
 * replace all occurencies if 'from' by 'to'.
 ******************************************************************************/
void ReplaceAll(std::string& s, const std::string& from, const std::string& to);



/*******************************************************************************
 * number conversion to std::string
 *   n         - number
 *   width     - minimum number of chars to print
 *   left      - left or right text padding
 *   precision - number of digits after period
 *   fill      - char to use for fill
 ******************************************************************************/
std::string IntToStr(std::intmax_t n);
std::string IntToStr(std::intmax_t n, size_t width, bool left);
std::string IntToStr(std::intmax_t n, size_t width, bool left, char fill);
std::string IntToHex(std::intmax_t n, size_t width);
std::string IntToOct(std::intmax_t n, size_t width);
std::string IntToBits(std::intmax_t n, size_t width);
std::string FloatToStr(double n);
std::string FloatToStr(double n, size_t width, size_t precision, bool left);
std::string ExpToStr(double n);
std::string ExpToStr(double n, size_t precision);



/*******************************************************************************
 * number conversion to std::wstring
 *   n         - number
 *   width     - minimum number of chars to print
 *   left      - left or right text padding
 *   precision - number of digits after period
 *   fill      - char to use for fill
 ******************************************************************************/
std::wstring IntToStrW(std::intmax_t n);
std::wstring IntToStrW(std::intmax_t n, size_t width, bool left);
std::wstring IntToStrW(std::intmax_t n, size_t width, bool left, wchar_t fill);
std::wstring IntToOctW(std::intmax_t n, size_t width);
std::wstring IntToHexW(std::intmax_t n, size_t width);
std::wstring IntToBitsW(std::intmax_t n, size_t width);
std::wstring FloatToStrW(double n);
std::wstring FloatToStrW(double n, size_t width, size_t precision, bool left);
std::wstring ExpToStrW(double n);
std::wstring ExpToStrW(double n, size_t precision);



/*******************************************************************************
 * std::string conversion to number. Prints to cerr on conversion failure.
 *   s         - string
 *   pos       - address of an size_t to store the number of chars processed,
 *               or nullptr
 *   base      - the number base
 * return value: converted number, or,
 *               if conversion fails INTMAX_MAX for int, NAN for double.
 *               Hint: use std::isnan() from <cmath> for NAN check.
 ******************************************************************************/
std::intmax_t StrToInt  (const std::string& s, size_t* pos = nullptr, size_t base = 0);
double        StrToFloat(const std::string& s, size_t* pos = nullptr);



/*******************************************************************************
 * std::wstring conversion to number. Prints to cerr on conversion failure.
 *   s         - string
 *   pos       - address of an size_t to store the number of chars processed,
 *               or nullptr
 *   base      - the number base
 * return value: converted number, or,
 *               if conversion fails INTMAX_MAX for int, NAN for double.
 *               Hint: use std::isnan() from <cmath> for NAN check.
 ******************************************************************************/
std::intmax_t WStrToInt  (const std::wstring& s, size_t* pos = nullptr, size_t base = 0);
double        WStrToFloat(const std::wstring& s, size_t* pos = nullptr);



/*******************************************************************************
 * returns a local time string 'dd.mm.yyyy HH:MM:SS' (German locale).
 * If t is given, it's read as a time_t.
 ******************************************************************************/
std::string TimeStr(std::intmax_t t = 0);



/*******************************************************************************
 * returns an ISO8601 time string: yyyy-mm-ddTHH:MM:SS{Z,+,−}[HH:MM].
 * example: 2024-02-18T12:47:27+01:00
 * If t is given, it's read as a time_t.
 ******************************************************************************/
std::string ISO8601Date(std::intmax_t t = 0);



/*******************************************************************************
 * conversion from 4-bit BCD value to decimal value, ie 0x0192 -> 192
 ******************************************************************************/
std::intmax_t BCDtoDecimal(std::intmax_t bcd);



/*******************************************************************************
 * sleep a thread using STL
 *   s         - seconds
 *   ms        - milliseconds
 *   us        - microseconds
 ******************************************************************************/
void Sleep(size_t s);
void mSleep(size_t ms);
void uSleep(size_t us);



/*******************************************************************************
 * HexDump() - print bytes human readable.
 *   intro     - caption string in utf8 (Note: 7bit ascii is valid utf8)
 *   buf       - pointer to buffer
 *   len       - length of buffer
 *   to_stderr - print to stderr, instead of stdout
 *   vec       - reference to vector of unsigned char, instead of buf and len
 ******************************************************************************/
void HexDump(std::string intro, const unsigned char* buf, size_t len, bool to_stderr = false);
void HexDumpW(std::wstring intro, const unsigned char* buf, size_t len, bool to_stderr = false);

void HexDump(std::string intro, std::vector<unsigned char>& vec, bool to_stderr = false);
void HexDumpW(std::wstring intro, std::vector<unsigned char>& vec, bool to_stderr = false);

void ByteDump(std::string intro, const uint8_t* buf, size_t len, bool to_stderr = false);
void WordDump(std::string intro, const uint16_t* buf, size_t len, bool to_stderr = false);
void DwordDump(std::string intro, const uint32_t* buf, size_t len, bool to_stderr = false);
void QwordDump(std::string intro, const uint64_t* buf, size_t len, bool to_stderr = false);



/*******************************************************************************
 * DirectoryExists() - returns true, if a directory exists.
 *   aDirectory - dir name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
bool DirectoryExists(std::string aDirectory);
bool DirectoryExistsW(std::wstring aDirectory);



/*******************************************************************************
 * FileExists() - returns true, if a file exists.
 *   aFile     - file name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
bool FileExists(std::string aFile);
bool FileExistsW(std::wstring aFile);



/*******************************************************************************
 * ExtractFilePath returns the path part from aFile. The path consists of all
 * characters before the last directory separator character ('/' or '\'),
 * including the directory separator itself.
 *   aFile     - file name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
std::string ExtractFilePath(std::string aFile);
std::wstring ExtractFilePathW(std::wstring aFile);



/*******************************************************************************
 * ExtractFileName returns the filename part from aFile. The filename consists
 * of all characters after the last directory separator character ('/' or '\').
 *   aFile     - file name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
std::string ExtractFileName(std::string aFile);
std::wstring ExtractFileNameW(std::wstring aFile);



/*******************************************************************************
 * CreateDir() - returns true, the if directory was successfully created.
 *   aDirectory - dir name in utf8 (Note: 7bit ascii is valid utf8)
 *   aMode      - dir permissions, ignored on MinGW.
 ******************************************************************************/
bool CreateDir(std::string aDirectory, size_t aMode = 0755);
bool CreateDirW(std::wstring aDirectory, size_t aMode = 0755);



/*******************************************************************************
 * RemoveDir() - returns true, the if directory was successfully removed.
 *   aDirectory - dir name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
bool RemoveDir(std::string aDirectory);
bool RemoveDirW(std::wstring aDirectory);



/*******************************************************************************
 * class cFileList - a list of files and subdirs of a directory.
 *   aDirectory - the directory to list.
 *   Filter     - partial name (case sensitive) of the files or
 *                directories to list. Empty for all files/dirs.
 ******************************************************************************/
class cFileList {
private:
  std::vector<std::string> priv;
public:
  cFileList(std::string aDirectory, std::string Filter = "");
  std::vector<std::string> List(void);
};



/*******************************************************************************
 * Read from or write to files.
 *   aFileName  - file to read or write.
 *   ss         - a stringstream to write into a file
 *   lines      - a vector of strings to write into a file
 *   empty      - read empty lines. skipped otherwise.
 *   return value
 *              Read* : a stringstream or vector of strings from the file.
 *              Write*: true on success.
 ******************************************************************************/
std::stringstream        ReadFileToStream(std::string aFileName);
std::vector<std::string> ReadFile(std::string aFileName, bool empty = false);

bool WriteStreamToFile(std::string aFileName, std::stringstream& ss);
bool WriteFile(std::string aFileName, std::vector<std::string>& lines);



/*******************************************************************************
 * IsAsciiFile() - returns true, if a file exists and is an ASCII file.
 * If the file contains any other character than horizontal tab, space or
 * printable ASCII chars, the function will return false.
 *   aFile     - file name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
bool IsAsciiFile(std::string aFileName);



/*******************************************************************************
 * Convert between UTF8 <-> UCS2 / UTF-32
 ******************************************************************************/
std::string  WStrToStr(std::wstring ws);
std::wstring StrToWStr(std::string s);



/*******************************************************************************
 * Wildcard match a string.
 *   String  - the string to be tested.
 *   Pattern - a search pattern in String.
 *             Matching Rules:
 *              1.  the asterisk character ('*', also called "star") matches
 *                  zero or more characters.
 *                  For example, "doc*" matches "doc" and "document",
 *                  but not "dodo".
 *              2.  the question mark '?' matches exactly one character.
 *                  For example, the pattern "123?" will match "1234",
 *                  but not "12345".
 *              3.  ranges of characters enclosed in square brackets,
 *                   '[' and ']', match a single character within the set.
 *                  For example, "[A-Za-z]" matches any single uppercase or
 *                  lowercase letter.
 *                  A leading caret '^' negates the set and matches only a
 *                  character not within the list.
 * returns true, if the pattern matches, false otherwise.
 ******************************************************************************/
bool Matches(std::string String, std::string Pattern);



/*******************************************************************************
 * Base64 encoding/decoding
 * ToBase64   encodes a vector of bytes into a base64 string.
 * FromBase64 decodes a base64 string into a vector of bytes.
 *
 *   bytes    - a vector of bytes, to be encoded into base64.
 *   s        - a base64 encoded string.
 *   alphabet - the base64 alphabet to be used for conversion,
 *              as a 64char string; ie. "ABCD..89+/"
 *
 * During encoding stuffing with one or two '=' chars is applied,
 * if the number of bytes is not a multiple of three.
 *
 * ToBase64   returns the base64 encoded string.
 * FromBase64 returns the raw bytes.
 ******************************************************************************/
std::string ToBase64(std::vector<uint8_t>& bytes, std::string& alphabet);
std::string ToBase64(std::vector<uint8_t>& bytes);
std::vector<uint8_t> FromBase64(std::string s, std::string& alphabet);
std::vector<uint8_t> FromBase64(std::string s);



/*******************************************************************************
 * Execute a process using popen().
 *
 *   process  - the full path to the command.
 *   message  - a string that receives the commands response.
 *
 * returns 0, if the command succeeded, non-zero otherwise.
 ******************************************************************************/
int SystemExecute(const std::string& process, std::string& message);



/*******************************************************************************
 * Download a file using system binary 'wget', using SystemExecute().
 *
 *   Addr     - the download address
 *   Dest     - the destination to store the file.
 *
 * returns the stdout of wget.
 ******************************************************************************/
std::string wget(std::string& Addr, std::string& Dest);



/*******************************************************************************
 * ThreadBase, a base class to control a child process.
 ******************************************************************************/
class ThreadBase {
private:
  std::promise<void> pObj;
  std::future<void>  fObj;
  std::thread tObj;
protected:
  /* A derived class needs to implement Action() to do it's task,
   * while periodically check Running() == true, ie in a loop.
   */
  virtual void Action(void) = 0;
  bool Running(void); // true, if job may continue.
public:
  ThreadBase();
  ThreadBase(ThreadBase&& other);
  virtual ~ThreadBase();
  ThreadBase& operator=(ThreadBase&& other);

  bool Start(void);  // Start the job
  void Cancel(void); // Stop the job
  void Join(void);   // Wait until job finished.
};



/*******************************************************************************
 * class cRunTime - measures the difference between two points in time,
 *                  may be used for optimize the run time of generated code.
 *   Start()        - trigger measurement
 *   Stop()         - stop measurement, triggered by Start()
 *   MilliSeconds() - the time im milli seconds, between Start() and Stop().
 ******************************************************************************/
class cRunTime {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> t1;
  std::chrono::time_point<std::chrono::high_resolution_clock> t2;
public:
  cRunTime(void) {}
  void Start(void);
  void Stop(void);
  double MilliSeconds(void);
  double MicroSeconds(void);
};



/*******************************************************************************
 * Appends vector Tail to vector Dest.
 ******************************************************************************/
template<class T> void AppendVector(std::vector<T>& Dest, std::vector<T>& Tail, bool Move = false) {
  if (Move and Dest.empty()) {
     Dest = std::move(Tail);
     return;
     }
  Dest.reserve(Dest.size() + Tail.size());
  Dest.insert(std::end(Dest), std::begin(Tail), std::end(Tail));
};



/*******************************************************************************
 * Version info. Returns a human readable version string, like "1.7.0".
 ******************************************************************************/
std::string RepfuncVersion(void);

