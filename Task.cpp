#include "Task.h"
#include "Utilities.h"
#include <iomanip>

size_t Task::field_width = 0;

Task::Task(const std::string&str)
{
   pNextTask[passed] = NULL; // initialize passed next task
   pNextTask[redirect] = NULL; // initialize redirect next task
   slots = "1";
   size_t next_pos = 0;
   bool more = true;
   int i = 0;
   Utilities util;
   while(more)
   {

      std::string token = util.nextToken(str, next_pos, more);

      if(i == 0)
      {

         name = token;

      }
      else if(i == 1)
      {

         slots = token;

      }
      else if(i == 2)
      {

         nextTask[passed] = token;

      }
      else if(i == 3)
      {

         nextTask[redirect] = token;

      }

      i++;

   }

   if (name.length() > field_width)
   {

      field_width = name.length();

   }

}

const std::string& Task::getName() const //- returns the name of the task
{

   return name;

}

unsigned int Task::getSlots() const //- returns the number of product slots in the task (converted from a string to an unsigned integer)
{

   return atoi(slots.c_str());

}

//- validates the next task(s), stored upon instantiation,
// by matching the name of each next task to task (referenced in this function's parameter).
// This function checks the name of each non-empty next task against task and,
// if the names match, stores the address of task in the pointer to that particular next task.
// This function then checks if the pointer to each non-empty next task has been resolved.
// If so, this function returns true.  This function always returns true if both next task names are empty.
bool Task::validate(const Task& task)
{

   if(nextTask[passed].length() == 0 && nextTask[redirect].length() == 0)
   {

      return true;

   }

   if(pNextTask[passed] == NULL && task.getName() == nextTask[passed] && task.getName().length() > 0)
   {

      pNextTask[passed] = &task;

   }
   else if(pNextTask[redirect]  == NULL && task.getName() == nextTask[redirect] && task.getName().length() > 0)
   {

      pNextTask[redirect] = &task;

   }

   return (nextTask[passed].length() == 0 || pNextTask[passed] != NULL)
          && (nextTask[redirect].length() == 0 || pNextTask[redirect] != NULL);

}

//- returns the address of the next task associated with the parameter received.
// This function reports an exception if the address (pNextTask) for a non-empty next task name
// corresponding to quality has not been resolved (as described in the validate() function).
// The form of the exception is *** Validate [...] @ [...] ***.

const Task* Task::getNextTask(Quality quality) const
{

   if(pNextTask[quality] == NULL)
   {

      std::string str;

      str = "*** Validate [";
      str += nextTask[quality];
      str += "] @ [";
      str += name;
      str += "] ***";

      throw str;

   }

   return pNextTask[quality];

}

void Task::display(std::ostream& os) const //- inserts into os a full description of the task as shown in the sample output listed below
//if the task has been validated //- uses the pointer(s) to the next task(s)
//if the task has not been validated //- uses the name(s) of the next task(s) and appends a note that validation is still required
{

   os << "Task Name    : [" << name << "]";

   for (size_t s = name.length(); s < field_width; s++)
   {

      os << " ";

   }

   os << " [" << getSlots() << "]\n";

   if (nextTask[passed].length() > 0)
   {

      os << " Continue to : [" << nextTask[passed] << "]";

      for (size_t s = nextTask[passed].length(); s < field_width; s++)
      {

         os << " ";

      }

      if (pNextTask[passed] == NULL)
      {

         os << " *** to be validated ***\n";

      }
      else
      {

         os << "\n";

      }

   }

   if (nextTask[redirect].length() > 0)
   {

      os << " Redirect to : [" << nextTask[redirect] << "]";

      for (size_t s = nextTask[redirect].length(); s < field_width; s++)
      {

         os << " ";

      }

      if (pNextTask[redirect] == NULL)
      {

         os << " *** to be validated ***\n";

      }
      else
      {

         os << "\n";

      }

   }

}

size_t Task::getFieldWidth() //- returns the field width currently stored for all objects in this class
{

   return field_width;

}

bool operator==(const Task& task_a, const Task& task_b)// - returns true if the tasks referenced in its parameters (task_a and task_b) have the same name
{

   return task_a.getName() == task_b.getName();

}

