
// C
#include <cassert>

// C++
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

using std::vector;
using std::cout;
using std::endl;
using std::string;

/// Task 1: Vector

void f(vector<int>& v) {
  v[0];
  v.at(0);
}

template<class Container, class OutputIterator>
OutputIterator copy_own(const Container& c, OutputIterator result) {
  return std::copy(c.begin(), c.end(), result);
}

TEST(SutterNew, Task1) {
  using std::ostream_iterator;
  using std::copy;

  vector<int> v;
  v.reserve(2);
  //assert(v.capacity() == 2);
  // скорее больше или равно, но вообще проверять смысле нет
  assert(v.capacity() >= 2);  // added

  // !!Compilde and work, but it's error
  //assert(v.size() == 2);  // added
  //v.at(0) = 1;  // added  throw exception
  v[0] = 1;  // error
  v[1] = 2;  // error

  // raw
  for (vector<int>::iterator i = v.begin();
       i < v.end(); i++) {
    cout << *i << endl;
  }

  // updated
  for (vector<int>::const_iterator i=v.begin(),  // const better if read only
      end=v.end();  // reduce extra calc
      i != end;  // < -> !=
      ++i) {
      cout << *i << '\n';  // endl сбрасывает буффер
  }

  // high level update - вообще дело вкуса
  // сразу пропадает ряд ошибок.
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));

  // high level - with const_iter
  copy_own(v, ostream_iterator<int>(cout, "\n"));

  // Next
  cout << v[0];  // maybe 1

  // Next
  v.reserve(100);
  //assert  // not need
  cout << v[0];  // 0
}

/// Task 2/3 Strings - sprintf
void PrettyFormat(int i, char* buf) {
  sprintf(buf, "%4d", i);  // C-version
  // DANGER0: переполнение 4 - минимальный размер
  // можно попробовать проверить, и передать размер буффера.
  // она что-то возвр. но это будет уже не важно
  // системы может к моменту проверки упасть.
  //
  // DANGER1: no type safe причем можно накосячить в шаблоне формата
  //
  // TROUBLE2: not work with templates.
}

// snprintf - гораздо безопаснее - DANGER0 - fix
// !! всегда использовать в С функции получ. буффер с длинной.
void PrettyFormat(int i, char *buf, int buflen) {
  snprintf(buf, buflen, "%4d", i);
}

// std::stringstream - looks like Java StringBuilder?
// Плюсы и минусы обратные sprintf
// Munuses:
//   - не просто и не ясно
//   - не эффективно
//
// Pluses:
template<class T>
void PrettyFormat(T i, string& s) {
  using std::ostringstream;
  using std::setw;

  ostringstream temp;
  temp << setw(4) << i;
  s = temp.str();

  //s = boost::lexical_cast<string>(i);  // без форматирования
}

// ostrstream - помечана устаревшей, но кажется неплохой у нее + - эффективность

TEST(SutterNew, Task3) {
  string s;
  PrettyFormat(9, s);
}

/// Task 4:  stl objs member-functions
// mem_fun
// p. 41 "невозможно создать указатель на функцию член станд. библ."
//
// http://stackoverflow.com/questions/2304203/how-to-use-boost-bind-with-a-member-function
//TODO: http://www.informit.com/articles/article.aspx?p=412354&seqNum=4

/// Task 5:




