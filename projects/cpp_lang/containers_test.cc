// Value based and ref-based interface
// http://www.boost.org/doc/libs/1_54_0/libs/ptr_container/doc/ptr_container.html
// https://tech.yandex.ru/events/yagosti/cpp-user-group/talks/1798/
//
// Chooose:
//   если длина известна, то лучше выбрать C-arr, std::array, boost::array -
//   "Opt. C++"
//
// (!): если очень мало пишем, но очень много ищем, то лучше использовать
// вектор, сортировать при добавлении и использовать алг. для
//   сорт. конейнеров, а не bst or hashtable. у вектора хорошая локальность
//   кеша. но что-то все равно с локальностью не так. или не вектор, если не
//   хранить в куче, а массив. но массивы не изменяемые по длине.
//
// Списки плохи для вычислений - плохая локалность ссылок
//
// Singly-linked lists - порой тоже полезны
//
#include "projects/view.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::ostreambuf_iterator;
using std::out_of_range;
using std::vector;
using view::operator<<;

/// Требования к объектам
// http://www.amse.ru/courses/cpp2/2011_02_21.html
// wiki
class STLObject {
public:
  // "копия эквив. оригиналу"? но тут похоже логика, что объект тот же
  // '==' реализовывать не обязательно. Просто должен быть точным клоном.
  STLObject(const STLObject &that);

  STLObject &operator=(const STLObject &that);

  ~STLObject();
  // operator==  //TODO: должно быть или нет?
  // operator<  //TODO: in assoc.?
private:
  // TODO: а конструктор может быть приватным?
};

TEST(STL, Vector) {
  // DANGER: пре перераспределении ссылки становятся не действительными?
  // Facts:
  //   Плохо если много векторов малого размера - неэфф. исп. память
  //   Емкость можно уменьшить через swap
  //   capacity() - сколько осталось до перераспределения

  //   v.at() - только она проверяет диапазон - out_of_range, front(), back()
  //   нужно проверять на пустоту
  vector<int> coll;
  assert(coll.empty());
  // coll[5] = 1;  // The program has unexpectedly finished.
  // cout << coll.front();  // The program has unexpectedly finished.
  if (coll.size() > 5)
    coll[5] = 1;
  if (!coll.empty())
    cout << coll.front();
  EXPECT_THROW(coll.at(5), out_of_range);

  // p. 163
  // Iterators
  // Не действительны, если удален или вставлен элемент с меньшим индексом или
  // перераспр. память
  vector<int>::iterator pos;
  pos = find(coll.begin(), coll.end(), 0);
  if (pos != coll.end())
    coll.erase(pos);

  // as Arrays
  if (!coll.empty()) {
    // func(coll.begin());  // нельзя так, возвращается итератор. но и не
    // компилир.
    int *arr_ok = &coll[0];
  }

  // Гарантии при работе с исключениями
  // ...
  // Если Assign Op and Copy Ctor не генерят искл., то insert либо вып. либо не
  // вносит изменений swap - не генерирует искл.

  // vector<bool> немного другой
}

TEST(STL, Deque) {
  // p. 171
  // at() - не генерирует искл.
  // Не совсем точно но:
  //   любая вставка/уд. делает недейств. итераторы => если программа хранит
  //   какие-то ссылки, то лучше его не выбирать
}

TEST(STL, List) {
  // Big: p. 180 - транзакционная безопасность при некоторых условиях
  // Нет произвольного доступа
  // Но быстрая вставка и удаление
  // Поддерживает много функция по перемещению
  list<int> l;

  if (!l.empty())
    int back = l.back(); // front()

  // К произвольному месту - только через итераторы и те двунаправленные
  // BiIterators
  // https://www.sgi.com/tech/stl/BidirectionalIterator.html
  l.insert(l.begin(), 8, 9);
  l.insert(l.begin()++, 8);  // into begin
  l.insert(++l.begin(), 78); // into after begin
  l.insert(l.end(), 90);     // добавляет

  // http://stackoverflow.com/questions/10793404/behaviour-of-stdlistbegin-when-list-is-empty
  // Лучше наверное так не делать
  // добавляет в начало! может из-за того что двунаправленный список - нет не
  // циркулярный список
  // l.insert(++l.end(), 90);
  cout << l;
  l.remove(9);
  cout << l;

  //
  /// выделяется операция splice - она не копирует, что важно при работе с двуму
  /// разными списками
  // http://stackoverflow.com/questions/15612700/stl-listsplice-iterator-validity
  list<int> c2;
  c2.insert(c2.begin(), 7, 3);

  l.splice(l.begin(), c2, ++c2.begin()); // move one element

  l.splice(l.begin(), c2, ++c2.begin(), --c2.end()); // move range

  cout << l << c2;
}
