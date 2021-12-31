// http://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm

// g++ -I../../third_party/loki-0.1.7/include postgres_forge.cc -lpqxx -lpq -o postgres_forge

// TODO: relations One-to...
// http://code.tutsplus.com/articles/sql-for-beginners-part-3-database-relationships--net-8561
//
// TODO: триггеры и хранимые процедуры
//
// TODO: как спрятать sql-код?
//
// TODO: queries
// http://technet.microsoft.com/en-us/library/bb264565(v=sql.90).aspx
// Может использовать паттерн спецификация? and().or() как в Objectify, хотя она NoSQL...
// Есть выборки по отношению! См к классике.

#include <typeinfo>

#include <cassert>

// C++
#include <iostream>
#include <string>

// 3rdpaty
// Common
#include <loki/ScopeGuard.h>

// Special
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;
using namespace Loki;

string gTableName = "company";

void rm_table(connection* C) {
  // Если таблицы нет, то просто ничего не происходит.
  string sql = string("drop table " + gTableName + ";");
  
  // создаем транзакционный объект
  work W(*C);
  
  cout << "Dropping" << endl;
  
  // Exec
  W.exec(sql);
  W.commit();
}

void run_transaction(const string& sql, /*const*/ connection& C)  
{
  work W(C);
  W.exec(sql);
  W.commit();
}

int main(int argc, char* argv[])
{
  try {
    // construction is safe? 
    connection C("dbname=mydb user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    {
      // DANGER: Рефакторинг мог быть не эквивалентным, но в api сказано, что закрывает только откр. соед.
      if (!C.is_open()) {
	//guard.Dismiss();  // not need it
	throw runtime_error("Can't open database");
      }
      
      ScopeGuard guard = MakeObjGuard(C, &connection::disconnect);
      {
	//ScopeGuard table = MakeGuard(&rm_table, &C);  // а если не создасться? Тут похоже все равно.
	
	{ // Create table 
	  // TODO: create only if not exist - с исключением не катит.
	  // TODO: а кто вообще создает таблицы? Всегда ли пользователь?
	  //
	  // TODO: как безболезненной сделать изменение схемы хранения? Как делать рефакторинг?
	  string sql = string("CREATE TABLE ") +  
	    // http://stackoverflow.com/questions/1766046/postgresql-create-table-if-not-exists
	    "IF NOT EXISTS "+ // v9.1 >=
	    gTableName +
	    "(" \
	    // http://www.tutorialspoint.com/postgresql/postgresql_using_autoincrement.htm
	    //"ID INT PRIMARY KEY NOT NULL," \  // own control
	    "ID SERIAL PRIMARY KEY NOT NULL," \
	    "NAME  TEXT NOT NULL " \
	    "AGE INT NOT NULL," \
	    "ADDRESS CHAR(50),"\
	    "SALARY REAL);";
	  
	  // создаем транзакционный объект
	  run_transaction(sql, C);
	}
	
	// Лучше здесь - раз дошли до сюда, то таблица создана
	ScopeGuard table = MakeGuard(&rm_table, &C);
	
	{
	  // Insert
	  // http://stackoverflow.com/questions/7718585/set-auto-increment-primary-key-in-postgresql
	  //string sql = "INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY) " \
	  //"VALUES (1, 'Paul', 32, 'Calif', 200000.00); ";
	  
	  string sql = "INSERT INTO " + gTableName + " (NAME, AGE, ADDRESS, SALARY) " \
	  "VALUES ('Paul', 32, 'Calif', 200000.00); " \
	  "VALUES ('Djudy', 32, 'Calif', 900000.00); ";
	  
	  run_transaction(sql, C);
	}
      }
    }

    // POINT - disconnected
    assert(!C.is_open());
    
  } catch (const pqxx::undefined_table& e) {
    // Нет таблицы
    cerr << typeid(e).name() << endl << e.what() << endl;
  } catch (const pqxx::unique_violation& e) {
    // Не уникальный ключ при вствке
    cerr << typeid(e).name() << endl << e.what() << endl;
  } catch (const pqxx::sql_error& e) {
    // Кажется ошибка в синтаксисе
    cerr << typeid(e).name() << endl << e.what() << endl;
  } catch (const std::exception& e) {
    cerr << "UNCATCHED" << endl;
    cerr << typeid(e).name() << endl;
    cerr << e.what() << std::endl;
    return 1;
  }
}