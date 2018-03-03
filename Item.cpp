#include "Item.h"
#include "Utilities.h"
#include <iomanip>

size_t Item::field_width = 1;

Item::Item(const std::string& str)
{
   description = "no detailed description";
   code = 1;
   size_t next_pos = 0;
   bool more = true;
   if(str.empty())
   {
      return;
   }
   Utilities util;
   std::string token = util.nextToken(str,next_pos,more);
   if(token.empty())
   {
      throw std::string("name is required field and it is missing");
   }
   name = token;
   token = util.nextToken(str,next_pos,more);
   if(token.empty())
   {
      throw std::string("filler is required field and it is missing");
   }
   filler = token;
   token = util.nextToken(str,next_pos,more);
   if(token.empty())
   {
      throw std::string("remover is required field and it is missing");
   }
   remover = token;
   token = util.nextToken(str,next_pos,more);
   if(!token.empty())
   {
      code = atoi(token.c_str());
   }
   token = util.nextToken(str,next_pos,more);
   if(!token.empty())
   {
      description = token;
   }

   if(name.length() > field_width)
   {

      field_width = name.length();

   }
   if(filler.length() > field_width)
   {

      field_width = filler.length();

   }
   if(remover.length() > field_width)
   {

      field_width = remover.length();

   }

}

bool Item::empty() const
{
   return name.empty();
}
Item& Item::operator++(int)
{

   code++;
   return *this;

}
unsigned int Item::getCode() const
{
   return code;
}
const std::string& Item::getName() const
{
   return name;
}
const std::string& Item::getFiller() const
{
   return filler;
}
const std::string& Item::getRemover() const
{
   return remover;
}
void Item::display(std::ostream& os,bool bFull) const
{

   os << "Task Name    : " << name << "";

   for(size_t s = name.length(); s < field_width; s++)
   {

      os << " ";

   }

   os << " [" << std::setfill('0') << std::setw(CODE_WIDTH) << code << "]";

   os << " From " << filler ;

   for(size_t s = filler.length(); s < field_width; s++)
   {

      os << " ";

   }

   os << " To " << remover;

   for(size_t s = remover.length(); s < field_width; s++)
   {

      os << " ";

   }

   if(bFull)

   {
      for(size_t s = 0; s < field_width + 4; s++)
      {

         os << " ";

      }

      os << ": " << description;

   }

   os << std::endl;



}

