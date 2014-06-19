#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;
using std::out_of_range;

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

void func(int* p) {
}

TEST(STL, Vector) {
  // DANGER: пре перераспределении ссылки становятся не действительными?
  // Facts:
  //   Плохо если много векторов малого размера - неэфф. исп. память
  //   Емкость можно уменьшить через swap
  //   capacity() - сколько осталось до перераспределения

  //   v.at() - только она проверяет диапазон - out_of_range, front(), back() нужно проверять на пустоту
  vector<int> coll;
  assert(coll.empty());
  //coll[5] = 1;  // The program has unexpectedly finished.
  //cout << coll.front();  // The program has unexpectedly finished.
  if (coll.size() > 5)
    coll[5] = 1;
  if (!coll.empty())
    cout << coll.front();
  EXPECT_THROW(coll.at(5), out_of_range);

  // p. 163
  // Iterators
  // Не действительны, если удален или вставлен элемент с меньшим индексом или перераспр. память
  vector<int>::iterator pos;
  pos = find(coll.begin(), coll.end(), 0);
  if (pos != coll.end())
    coll.erase(pos);

  // as Arrays
  if (!coll.empty()) {
    //func(coll.begin());  // нельзя так, возвращается итератор. но и не компилир.
    int* arr_ok = &coll[0];
  }

  // Гарантии при работе с исключениями
  // ...
  // Если Assign Op and Copy Ctor не генерят искл., то insert либо вып. либо не вносит изменений
  // swap - не генерирует искл.

  // vector<bool> немного другой
}

TEST(STL, Deque) {

}
