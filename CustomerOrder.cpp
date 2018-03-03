#include "CustomerOrder.h"
#include "Utilities.h"
#include "CustomerItem.h"
#include "Item.h"
#include <vector>

size_t CustomerOrder::field_width = 1;

CustomerOrder::CustomerOrder(const std::string& str)
{
   order = NULL;
   nOrders = 0;
   size_t next_pos = 0;
   bool more = true;
   Utilities util;
   std::string token = util.nextToken(str,next_pos,more);
   if(token.empty())
   {
      throw std::string("customer name is required field and it is missing");
   }
   name = token;
   token = util.nextToken(str,next_pos,more);
   if(token.empty())
   {
      throw std::string("product name is required field and it is missing");
   }
   product = token;
   std::vector < std::string > items;
   while(more)
   {
      token = util.nextToken(str,next_pos,more);
      if(!token.empty())
      {
         items.push_back(token);
      }
   }

   nOrders = items.size();
   order = new CustomerItem[nOrders];
   for(size_t i = 0; i < nOrders; i++)
   {
      order[i] = CustomerItem(items[i]);
   }


   if(name.length() > field_width)
   {

      field_width = name.length();

   }

   if(product.length() > field_width)
   {

      field_width = product.length();

   }

}
CustomerOrder::CustomerOrder(const CustomerOrder& o)
{

   throw std::string("copy constructor must not be called");
   //name = o.name;
   //product = o.product;
   //nOrders = o.noOrders;
   //order = new CustomerOrder[nOrders];
   //for(size_t i = 0; i < nOrders; i++)
   //{
   //   order[i] = o.order[i];
   //}

}
CustomerOrder::CustomerOrder(CustomerOrder&& o) NOEXCEPT
{
   operator = (std::move(o));
}
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& o)NOEXCEPT
{
   name = o.name;
   product = o.product;
   nOrders = o.nOrders;
   order = o.order;
   o.order = NULL;
   o.nOrders = 0;
   return std::move(*this);
}
CustomerOrder::~CustomerOrder()
{

   if(order != NULL)
   {
      delete[] order;
   }
}
unsigned int CustomerOrder::noOrders() const
{
   return nOrders;
}
const std::string& CustomerOrder::operator[](unsigned int i) const
{
   return order[i].getName();
}
void CustomerOrder::fill(Item&item)
{

   for(unsigned int i = 0; i < nOrders; i++)
   {

      if(order[i].asksFor(item))
      {

         order[i].fill(item.getCode());

         item++;

      }

   }

}

void CustomerOrder::remove(Item& item)
{
   for(unsigned int i = 0; i < nOrders; i++)
   {

      if(order[i].isFilled() && order[i].asksFor(item))
      {

         order[i].clear();

      }

   }


}
bool CustomerOrder::empty() const
{
   return nOrders == 0;
}
void CustomerOrder::display(std::ostream& os) const
{
   os << name;

   for(size_t s = name.length(); s < field_width; s++)
   {

      os << " ";

   }
   os << " : " << product;

   for(size_t s = name.length(); s < field_width; s++)
   {

      os << " ";

   }
   os << "\n";

   for(unsigned int i = 0; i < nOrders; i++)
   {

      order[i].display(os);


   }

}
