#include "TaskManager.h"
#include "ItemManager.h"
#include <algorithm>

//class TaskManager : public std::vector<Task>
void TaskManager::validate(std::ostream& os)
{
   bool valid = true;
   for (auto i = 0u; i < size() && valid; i++)
   {
      bool invalid = true;
      for (auto j = 0u; j < size() && invalid; j++)
      {
         if (operator[](i).validate(operator[](j)))
            invalid = false;
      }
      valid = !invalid;
   }
   if (!valid)
      os << "*** Not all Tasks have been validated ***\n";


}

void TaskManager::validate(const ItemManager& item_manager, std::ostream& os)
{

   for (auto & item : item_manager)
   {

      if (std::find_if(cbegin(), cend(), [&](const Task & task)
   {
      return task.getName() == item.getRemover();
      }) == cend())
      {
         os << item.getRemover() << " is unavailable\n";
      }


      if (std::find_if(cbegin(), cend(), [&](const Task & task)
   {
      return task.getName() == item.getFiller();
      }) == cend())
      {
         os << item.getFiller() << " is unavailable\n";
      }

   }





}

void TaskManager::display(std::ostream& os) const
{
   for (auto& t : *this)
      t.display(os);
}

