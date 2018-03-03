#include "ItemManager.h"


//class ItemManager : public std::vector<Item>

void ItemManager::display(std::ostream& os, bool bFull/*= false*/) const
{

   for (auto & item : *this)
   {

      item.display(os, bFull);

   }

}
