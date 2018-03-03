#include "Utilities.h"
#include <algorithm>
#include <functional>
#include <cctype>
// trim from start (in place)
static inline void ltrim(std::string &s)
{
   s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                   std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
   s.erase(std::find_if(s.rbegin(), s.rend(),
                        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
   ltrim(s);
   rtrim(s);
}
// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
   ltrim(s);
   return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
   rtrim(s);
   return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
   trim(s);
   return s;
}

char Utilities::delimiter = 0;
std::ofstream Utilities::logFile;

Utilities::Utilities()
{
   field_width = 1;

}



//Upon instantiation, a Utilities object initializes the value of its field_width instance variable to 1.
//The member functions of the Utilities class include:
void Utilities::setFieldWidth(size_t fw)// - resets the field width of the current object to fw
{

   field_width = fw;

}


size_t Utilities::getFieldWidth() const// - returns the field width of the current object
{

   return field_width;

}
// - receives a reference to string str, a reference to the position (next_pos) in this string at which to start extraction,
// and a reference to a boolean flag (more).
// This function returns the next token found and sets more to true if the record contains more tokens after the extracted token; false otherwise.
// This function updates the current object's field_width data member if its current value is less than the size of the token extracted.
// This function reports an exception if there are two delimiters with no token between them.
const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more)
{

   more = true;

   size_t start = next_pos;

   while(next_pos < str.length())
   {

      if(str[next_pos] == delimiter)
      {

         if(next_pos - start == 0)
         {
            std::string strError;

            strError = str;

            strError += "<-- *** no token found before the delimiter ***";

            throw strError;


         }

         next_pos++;
         more = next_pos < str.length();

         return trim_copy(str.substr(start, next_pos - start - 1));

      }
      next_pos++;

   }
   more = false;
   return trim_copy(str.substr(start, next_pos-start));

}
void Utilities::setDelimiter(const char ch) //- resets the delimiter for this class to the character received
{

   delimiter = ch;
}
// - receives the address of an unmodifiable C-style string containing the name of the log file for the project.
//  This function opens a file of this name for writing and truncation.
void Utilities::setLogFile(const char* logfile)
{
   logFile.open(logfile);
}

std::ofstream& Utilities::getLogFile() //- returns a modifiable reference to the log file
{

   return logFile;

}
