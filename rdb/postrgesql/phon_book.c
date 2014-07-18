// gcc phon_book.c -lpq -o phon_book

// C
#include <stdio.h>
#include <assert.h>

// 3rdparty
#include <postgresql/libpq-fe.h>

// C++


int main() {
  PGconn *conn;
  PGresult *result;
  int rec_count;
  int row;
  int col;
  
  conn = PQconnectdb("dbname=mydb host=localhost user=postgres password=postgres");
  assert(PQstatus(conn) != CONNECTION_BAD);
  
  
  //
  PQfinish(conn);
}