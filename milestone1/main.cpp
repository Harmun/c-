#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Task.h"
#include "Utilities.h"

int main(int argc, char** argv)
{
   if (argc != 3)
   {
      std::cerr << "argnuminvalid\n"
                << "Usage: " << argv[0] << " tasks_file field_delimiter\n";
      return 1;
   }

   Utilities::setLogFile("log.txt");


   std::ifstream f(argv[1]);

   if(f.fail())
   {

      std::cerr << "Failed to open file" << argv[1];
      return 0 ;

   }

   Utilities::setDelimiter(argv[2][0]);

   std::vector < Task > taska;

   std::cout << "Acquiring the Set of Tasks\n";
   std::cout << "--------------------------\n";

   while(!f.eof())
   {


      std::string str;

      std::getline(f, str);
      try
      {

         taska.push_back(Task(str));

      }
      catch (const std::string & strError)
      {

         std::cout << str << "<-- " << strError << std::endl;
      }


   }

   std::cout << "\n";
   std::cout << "Accepted Set of Tasks\n";
   std::cout << "---------------------\n";
   for (size_t i = 0; i < taska.size(); i++)
   {

      try
      {

         taska[i].display(::std::cout);
      }
      catch (const std::string & strError)
      {
         std::cout << strError << std::endl;
      }


   }


   std::cout << "\n";
   std::cout << "Check Next Tasks\n";
   std::cout << "----------------\n";
   for (size_t i = 0; i < taska.size(); i++)
   {

      for (size_t j = i + 1; j < taska.size(); j++)
      {

         taska[i].validate(taska[j]);

      }

   }
   ::std::cout << "*** Further checks suspended ***\n";
   ::std::cout << "\n";

   ::std::cout << "Validating the Set of Tasks\n";
   ::std::cout << "---------------------------\n";
   ::std::cout << "\n";

   for (size_t i = 0; i < taska.size(); i++)
   {

      taska[i].display(::std::cout);

   }

   //#checkiffileopened
   //#utilities constructor set a dilimiter
   //#task::setdelimiter
   //#set vector<tasks> tasks
   //loop for task records and use push_back
   //display accepted set of tasks

   //check next tasks

   //validate tasks
   std::cout << std::endl;
   std::cout << "Done!\n";
   std::cout << "Press Enter Key to Exit ...\n";
   getchar();

   return 1;

}
