#include "OrderManager.h"
#include "ItemManager.h"
#include <algorithm>

//class OrderManager : public std::vector<CustomerOrder>

CustomerOrder && OrderManager::extract()
{
   CustomerOrder && order = std::move(back());
   pop_back();
   return std::move(order);
}


void OrderManager::validate(const ItemManager& item_manager, std::ostream& os)
{


   for (auto & order : *this)
   {

      for (size_t i = 0; i < order.noOrders(); i++)
      {

         if (std::find_if(item_manager.cbegin(), item_manager.cend(), [&](const Item & item)
      {
         return order[i] == item.getName();


         }) == item_manager.cend())
         {
            os << order[i] << " is unavailable\n";
         }

      }

   }

}


void OrderManager::display(std::ostream& os) const
{
   for (auto& o : *this)
      o.display(os);
}
