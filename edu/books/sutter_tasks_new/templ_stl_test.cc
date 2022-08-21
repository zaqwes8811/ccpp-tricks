
// C
#include <cassert>

// C++
#include <gtest/gtest.h>

#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/// Task 1: Vector

void f(vector<int> &v) {
    v[0];
    v.at(0);
}

template <class Container, class OutputIterator>
OutputIterator copy_own(const Container &c, OutputIterator result) {
    return std::copy(c.begin(), c.end(), result);
}

TEST(SutterNew, Task1) {
    using std::copy;
    using std::ostream_iterator;

    vector<int> v;
    v.reserve(2);
    // assert(v.capacity() == 2);
    //  скорее больше или равно, но вообще проверять смысле нет
    assert(v.capacity() >= 2);  // added

    // !!Compilde and work, but it's error
    // assert(v.size() == 2);  // added
    // v.at(0) = 1;  // added  throw exception
    v[0] = 1;  // error
    v[1] = 2;  // error

    // raw
    for (vector<int>::iterator i = v.begin(); i < v.end(); i++) {
        cout << *i << endl;
    }

    // updated
    for (vector<int>::const_iterator i = v.begin(),  // const better if read only
         end = v.end();                              // reduce extra calc
         i != end;                                   // < -> !=
         ++i) {
        cout << *i << '\n';  // endl сбрасывает буффер
    }

    // high level update - вообще дело вкуса
    // сразу пропадает ряд ошибок.
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));

    // high level - with const_iter
    copy_own(v, ostream_iterator<int>(cout, "\n"));

    // Next
    // cout << v[0];  // maybe 1

    // Next
    v.reserve(100);
    // assert  // not need
    // cout << v[0];  // maybe 0
}

/// Task 2/3 Strings - sprintf
void PrettyFormat(int i, char *buf) {
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
void PrettyFormat(int i, char *buf, int buflen) { snprintf(buf, buflen, "%4d", i); }

// std::stringstream - looks like Java StringBuilder?
// Плюсы и минусы обратные sprintf
// Munuses:
//   - не просто и не ясно
//   - не эффективно
//
// Pluses:
template <class T>
void PrettyFormat(T i, string &s) {
    using std::ostringstream;
    using std::setw;

    ostringstream temp;
    temp << setw(4) << i;
    s = temp.str();

    // s = boost::lexical_cast<string>(i);  // без форматирования
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
// TODO: http://www.informit.com/articles/article.aspx?p=412354&seqNum=4

/// Task 5:
// Недостатки полиморф. вр. вып.
//   - вирт. таблица - как-то так это называется
//   - используется наследование
//
// Полиморфизм времени компиляции - можно обойтись без наследования
//
template <class T1, class T2>  // два типа!!
void construct(T1 *p, const T2 &value) {
    new (p) T1(value);  // placment new
                        // http://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new
    // http://stackoverflow.com/questions/15254/can-placement-new-for-arrays-be-used-in-a-portable-way
}

TEST(SutterNew, Task5) {
    int *p = new int;
    double i = 0;
    construct(p, i);  // TODO: компилируется, а должно?

    // mem leak
}

/// Task 6:
template <class T>
void destroy(T *p) {
    p->~T();
}

// Trouble: FwdIter может быть только указателем
// Итераторы не всегда указатели
template <class FwdIter>
void destroy(FwdIter first, FwdIter last) {
    while (first != last) {
        // destroy(first);
        destroy(&*first);  // any iterator
        ++first;
    }
}

// p. 48
// TODO: понял не до конца
// no exception safe
// TODO: что за побочные действия оператора Т?
template <class T>
void swap(T &a,
          T &b) {  // лучше переопределить через T::swap в другом простр. имен
    T temp(a);
    a = b;     // may throw
    b = temp;  // may throw - a is changed!!
}

/// Task 7:
// TODO: мало знаю о шаблонах, поэтому мало ясно. Что-то про специализацию и
//    перегрузку функций.

/// Task 8: о дружественных шаблонах
// TODO: шаблономагия

/// Task 9: export
// TODO: шаблономагия

/// Task 10: export
// TODO: шаблономагия
