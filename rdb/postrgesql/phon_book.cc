// http://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm

// g++ -I../../third_party/loki-0.1.7/include phon_book.cc -lpqxx -lpq -o phon_book

#include <iostream>
#include <pqxx/pqxx> 

#include <loki/ScopeGuard.h>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   try{
      connection C("dbname=mydb user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
      
      if (C.is_open()) {
         cout << "Opened database successfully: " 
	  << C.dbname() 
	  << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      C.disconnect();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
}