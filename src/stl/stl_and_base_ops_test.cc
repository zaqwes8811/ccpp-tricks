#include <vector>
#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;

/// Требования к объектам
// http://www.amse.ru/courses/cpp2/2011_02_21.html
// wiki
class STLObject {
public:
  // "копия эквив. оригиналу"? но тут похоже логика, что объект тот же
  // '==' реализовывать не обязательно. Просто должен быть точным клоном.
  STLObject(const STLObject& that);
  STLObject& operator=(const STLObject& that);
  ~STLObject();
  //operator==  //TODO: должно быть или нет?
  //operator<  //TODO: in assoc.?
private:
  //TODO: а конструктор может быть приватным?
};

TEST(STL, StreamIterators) {
  vector<int> a(5, 8);
  copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
  cout << endl;
}

TEST(STL, BinaryPredicats) {
  //TODO:
  // Важно понять какие совойства должны быть и для каких операций
  // '=='
  //   транзитивность
}
