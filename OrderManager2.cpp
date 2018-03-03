#include "OrderManager.h"

//class OrderManager : public std::vector<CustomerOrder>

CustomerOrder && OrderManager::extract()
{
   CustomerOrder && order = std::move(back());
   pop_back();
   return std::move(order);
}


void OrderManager::validate(const ItemManager& item_manager, std::ostream& os)
{
   for (auto & item : item_manager)
   {

      if (std::find_if(cbegin(), cend(), [&](const CustomerOrder & order)
   {
      return order.getName() == item.getName();
      }) == cend())
      {
         os << item.getName() << " is unavailable\n";
      }

   }

}


void OrderManager::display(std::ostream & os) const
{
	for (auto& o : *this)
		o.display(os);
}
