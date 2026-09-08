/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::string
#include <iostream>  // std::cout
#include <repfunc.h> // include this library

int main() {
  std::cout << "/*************************************************************\n"
            << " * Please read this article:\n"
            << " *   https://en.wikipedia.org/wiki/Base64\n"
            << " ************************************************************/\n"
            << "\n\n\n";

  std::cout << "== Examples ==\n\n";

  std::cout << "The example below uses ASCII text for simplicity, but this is"
            << " not a typical use\ncase, as Base64 encoded text can be safely "
            << "transferred across all systems that \ncan handle Base64.\nThe "
            << "more typical use is to encode binary data (such as an image);\n"
            << "the resulting Base64 data will only contain 64 different ASCII"
            << " characters, all\nof which can reliably be transferred across "
            << "systems that may corrupt the raw\nsource bytes.\n\n";

  std::cout << "Here is a well-known idiom from distributed computing:\n";

  std::string s("Many hands make light work.");
  std::cout << "'" << s << "'\n\n";

  std::cout << "When the quote is encoded into Base64, it is represented as a "
            << "byte sequence of \n8-bit-padded ASCII characters encoded in "
            << "MIME\'s Base64 scheme as follows\n(newlines and white spaces "
            << "may be present anywhere but are to be ignored on\ndecoding):"
            << "\n\n";

  std::vector<uint8_t> bytes(s.data(),s.data()+s.size());
  std::cout << "'" << ToBase64(bytes) << "'\n\n\n";


  bytes.erase(bytes.begin()+3,bytes.end());
  std::cout << "In the above quote, the encoded value of 'Man' is '"
            << ToBase64(bytes) << "'.\nEncoded in ASCII,the characters "
            << "'M', 'a', and 'n' are stored as the byte "
            << "values\n "
            << IntToHex('M',2) + ", " + IntToHex('a',2) + ", and " + IntToHex('n',2)
            << ", which are the 8-bit binary values\n"
            << IntToBits('M',8) + ", " + IntToBits('a',8) + ", and " + IntToBits('n',8)
            << ".\nThese three values are joined together into a 24-bit string,\n"
            << "producing '" + IntToBits('M'<<16 | 'a'<<8 | 'n',24) + "'.\n\n"
            << "Groups of 6 bits (6 bits have a maximum of 64 different "
            << "binary values) are\nconverted into individual numbers from "
            << "start to end (in this case, there are\nfour numbers in a "
            << "24-bit string), which are then converted into their\n"
            << "corresponding Base64 character values.\n\n";

  std::cout << "== Output padding ==\n\n";

  std::cout << "Because Base64 is a six-bit encoding, and because the decoded"
            << " values are divided\ninto 8-bit octets on a modern computer,"
            << " every four characters of Base64-encoded\ntext (4 sextets = "
            << "4 × 6 = 24 bits) represents three octets of unencoded text or\n"
            << "data (3 octets = 3 × 8 = 24 bits). This means that when the "
            << "length of the\nunencoded input is not a multiple of three, the "
            << "encoded output must have padding\nadded so that its length is a"
            << " multiple of four. The padding character is '=',\nwhich "
            << "indicates that no further bits are needed to fully encode the "
            << "input.\n(This is different from A, which means that the remain"
            << "ing bits are all zeros.)\nThe example below illustrates how tru"
            << "ncating the input of the above quote\nchanges the output "
            << "padding:\n\n";


  s = "light work.";
  bytes = std::vector<uint8_t>(s.data(),s.data()+s.size());
  for(int i=0; i<5; i++) {
     HexDump("Input", bytes);
     auto enc = ToBase64(bytes);
     int padding = (bytes.size()%3) == 0 ? 0 : 3 - (bytes.size()%3);
     std::cout << "   Output = '" << enc << "'"
               << ", length = " << IntToStr(enc.size())
               << ", padding = " << IntToStr(padding) << "bytes"
               << "\n\n\n\n";
     bytes.pop_back();
     }



  std::cout << "== Decoding Base64 with padding ==\n\n";

  std::cout << "When decoding Base64 text, four characters are typically "
            << "converted back to\nthree bytes. The only exceptions are when "
            << "padding characters exist.\nA single '=' indicates that the "
            << "four characters will decode to only two\nbytes, while '==' in"
            << "dicates that the four characters will decode to only a\nsingle"
            << " byte.\n\n"
            << "For example:\n\n";

  std::vector<std::string> samples;
  samples.push_back("bGlnaHQgdw==");
  samples.push_back("bGlnaHQgd28=");
  samples.push_back("bGlnaHQgd29y");

  for(auto s:samples) {
     bytes = std::vector<uint8_t>(s.data(),s.data()+s.size());
     size_t padding = s.find('=') == std::string::npos ? 0: s.size() - s.find('=');
     auto dec = FromBase64(s);
     dec.push_back(0); // zero termination for use as const char*.
     std::cout << "Encoded = '" + s + "'  padding bytes = "
               << IntToStr(padding) << ", Length of last encoded triple = "
               << IntToStr(3-padding) << ", Decoded = '"
               << (const char*) dec.data() << "'" << std::endl;
     }
  std::cout << "\n\n";



  std::cout << "== Decoding Base64 without padding ==\n\n";

  std::cout << "Without padding, after normal decoding of four characters to "
            << "three bytes over\nand over again, fewer than four encoded char"
            << "acters may remain. In this\nsituation, only two or three chara"
            << "cters can remain. A single remaining enco-\nded character is not"
            << " possible, because a single Base64 character only contains\n 6"
            << " bits, and 8 bits are  required to create a byte, so a minimum "
            << "of two Base64\ncharacters are required: The first character con"
            << "tributes 6 bits, and the second\ncharacter contributes its first"
            << " 2 bits.\n\n"
            << "For example:\n\n";

  samples[0] = "bGlnaHQgdw";
  samples[1] = "bGlnaHQgd28";
  samples[2] = "bGlnaHQgd29y";

  for(auto s:samples) {
     bytes = std::vector<uint8_t>(s.data(),s.data()+s.size());
     size_t padding = (s.size() % 3) == 0 ? 0 : 3 - (s.size() % 3);
     auto dec = FromBase64(s);
     dec.push_back(0); // zero termination for use as const char*.
     std::cout << "Encoded = " + BackFill("'" + s + "'",14)
               << "  Length of last encoded triple = "
               << IntToStr(3-padding) << ", Decoded = '"
               << (const char*) dec.data() << "'" << std::endl;
     }
  std::cout << "\n\n";

  return 0;
}
