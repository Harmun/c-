#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>


CustomerItem::CustomerItem(const std::string& str)
{
   filled = false;
   name = str;
   code = 0;
}
bool CustomerItem::asksFor(const Item&item) const
{

   return item.getName() == name;

}
bool CustomerItem::isFilled() const
{
   return filled;
}
void CustomerItem::fill(const unsigned int i)
{
   code = i;
   filled = true;
}
void CustomerItem::clear()
{
   filled = false;
}
const std::string& CustomerItem::getName() const
{
   return name;
}
void CustomerItem::display(std::ostream& os) const
{
   if(filled)
   {
      os << "+ [";
   }
   else
   {
      os << "- [";

   }

   os << std::setfill('0') << std::setw(CODE_WIDTH) << (filled ? code : 0) << "] ";
   os << name << std::endl;

}
