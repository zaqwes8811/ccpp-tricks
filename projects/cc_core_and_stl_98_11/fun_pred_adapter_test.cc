// http://www.codeproject.com/Tips/537403/Cplusplus-Prefer-bind-to-bind-st-and-bind-nd
// http://www-h.eng.cam.ac.uk/help/tpl/languages/C++/bind.html
// bind2nd - op(a1, A2_conn)
// bind1st - op(A1_conn, a2)
//
// Note: В алгоритм можно передать и по ссылке, но тогда нужно полностью специфицировать шаблон.

// функторы передаются по значению
//   они должны быть малы и они не могут быть полиморфными. можно обернуть не удовл. классы.

#include "projects/view.h"

#include <gtest/gtest.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::ostreambuf_iterator;
using std::out_of_range;

using namespace std;
using namespace view;


TEST(STL, BinaryPredicats) {
    //TODO:
    // Важно понять какие совойства должны быть и для каких операций
    // '=='
    //   транзитивность
}

void func(int* p) {
}

// summary:
// p. 303 - не должен изменять состояние

class Nth {
private:
    int nth;
    int count;
public:
    Nth(int n) : nth(n), count(0) {}

    // лучше пердавать по значению или по конст. ссылке.
    // не должны менятся свойства как предиката, но константность лучше сперва поставить
    bool operator()(int) /* must be const, but accamulate? best make const */ {
        return ++count == nth;
    }
};

class IntSequence {
public:
    int value;
public:
    IntSequence(int ini) : value(ini) {}

    int operator()() {
        return value++;
    }
};

TEST(STL, PredicateWithState) {
    IntSequence a(1);
    a();
    a();
    assert(a.value == 3);
    IntSequence b = a;
    assert(b.value == 3);  // так а как состояние обнуляется? меняется копия!

    // функтор != предикат
    // for_each единственная может вернуть предикат - наверное не совсем предикат
}

TEST(STL, WrongPredicate) {
    using std::remove_if;

    list<int> coll;
    insert_elems(coll, 1, 9);
    print_elems(coll);

    // del 3
    list<int>::iterator pos;
    pos = remove_if(coll.begin(), coll.end(),
                    Nth(3));

    coll.erase(pos, coll.end());
    print_elems(coll, "nth removed: ");  // !! удален и 6 тоже!!
}

// http://easy-coding.blogspot.ru/2009/07/blog-post_25.html
// функтор быстрее указателя на функцию, но см. комменты
