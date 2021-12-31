// при работе с циклами могут быть проблемы с недействительностью итераторов.
//  но порой с циклами проще, если короче Мейсер stl
//


#include "projects/view.h"
#include "projects/std_own_ext.h"

#include <gtest/gtest.h>
#include <boost/range/end.hpp>
#include <boost/range/begin.hpp>

#include <vector>
#include <algorithm>
#include <ostream>
#include <list>

using namespace std;
using namespace view;//::operator<<;

// copy(... inserter/back_inserter/front_ins) -> должны заменяться интервальными функциями, insert, например

namespace {

struct LinearGen {
    LinearGen() : val(1) {}

    int operator()() {
        return val++;
    }

    int val;
};

bool bad_value(int x) {
    return x < 4;
}


bool rm_bad_value(int x) {
    return x == 7;
}

}  // names..

TEST(STL, RemoveInsertErase) {
    vector<int> v2;
    v2.assign(10, 1);
    //adobe::fill(v2  // одинаковые элементы в готовый контейнер
    generate_n(v2.begin(), 8, LinearGen());
    cout << v2;

    // Это лучше чем copy! важна семантика
    vector<int> v1;
    //v1.assign(v2.begin() + v2.end() / 2, v2.end());
    v1.assign(v2.begin() + v2.size() / 2, v2.end());
    v1.insert(v1.end(), v2.begin() + v2.size() / 2, v2.end());  // вставка
    v1.insert(v1.begin(), v2.begin() + v2.size() / 2, v2.end());  // вставка
    std::random_shuffle(v1.begin(), v1.end());
    cout << v1;

    // удаление
    // для списка лучше использовать собственное удаление
    v1.erase(std::remove(v1.begin(), v1.end(), 1), boost::end(v1)); // что-то не то
    cout << v1;

    //
    v1.erase(std::remove_if(v1.begin(), v1.end(), bad_value),
             boost::end(v1)  // !! Very important!! Without in compiled and work but it's incorrect
    );
    cout << v1;

    /// List
    list<int> l;
    l.assign(boost::begin(v2), boost::end(v2));
    cout << l;
    l.remove(1);  // реально удаляет
    cout << l;
    // http://cppstudio.com/post/282/
    l.erase(++l.begin());  // ++op - возвращает уже новое значение
    cout << l;

    // DANGER: удаление с выводом в лог - Eff. STL_9
    vector<int> v1_copy = v1;
    cout << v1_copy;
    for (vector<int>::iterator i = v1_copy.begin(); i != v1_copy.end();) {
        if (rm_bad_value(*i)) {
            cout << "Log: " << *i << endl;
            i = v1_copy.erase(i);
            cout << "Current it: " << *i << endl;
        } else {
            ++i;
        }
    }

}

/// Modif. algs
// - in work time
// - on copy

//Del
// для списков есть более эффективные функции
// те что с copy похоже не меняют входного интервала
TEST(STL, Remove_fun) {
    // http://www.gotw.ca/gotw/051.htm

    using std::less;

    vector<int> coll;
    insert_elems(coll, 2, 6);
    insert_elems(coll, 4, 9);
    insert_elems(coll, 1, 7);
    print_elems(coll, "coll: ");

    vector<int>::iterator pos;
    pos = remove(coll.begin(), coll.end(),
                 5);
    print_elems(coll, "size not changed: ");

    // своя erase уже знает что делать с элементами, на вход идут итератор
    vector<int>::iterator next = coll.erase(pos, coll.end());  // Возвращает VALIDE(!!!) итератор
    // с ассоциативными не все так просто.

    print_elems(coll, "size changed: ");

    coll.erase(remove_if(
        coll.begin(), coll.end(),
        bind2nd(less<int>(),
                4)),
               coll.end());
    print_elems(coll, "removed < 4: ");

    // удаления с копированием
    // http://stackoverflow.com/questions/11928115/why-doesnt-stdremove-copy-if-actually-remove
    coll.clear();
    insert_elems(coll, 1, 7);
    vector<int> c_save = coll;
    cout << coll;
    vector<int> e;
    remove_copy_if(coll.begin(), coll.end(), back_inserter(e), bind2nd(less<int>(), 4));
    cout << e << coll;
    assert(coll == c_save);

    //
    // FIXME: из-за особенностей remove возникает проблема с удалением
    //   указателей на динамическую память, или не управл. хендлов.
    // v0 - partion
    // v1 - delete, set null, del null - конт. не должен сод. null-elems
    //   !!! static_cast<Widget*>(0) !!! не просто 0

    // copy_if
    // remove_copy_if(begin,end,destBegin,not1(p));  // !BAD impl
}

TEST(stl, unique_fun) {
    // удаляем одинаковые соседние, либо условно копирует

}


// важно что происходит и удаление и обход. может быть цикл слишком много на себя берет?






