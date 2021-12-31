/// "Easy reason about." Если в цикле много условий то не слишком ли он много на себя берет?
//
// http://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning
//

// Raw loop - A raw loop is any loop inside function where the function serve purpose larger then
// tha algorithm implemented by the loop.
//
//Why no raw loops?
//- Difficule reason about and dificult to prove post conditions
//- Error prone and likly to fail under non-obvios conditions
//- Introduce non-obvios performance problems
//- Complicates reasoning about the surronding code
// - отравляет код вокруг цикла
//
// Alternatives:
// - Use an existing alg. (Prefer standart algs if availabel)
// - Implement a know algorithm as a general function (contribute to library - внутреннюю или открытую
//   сперва нужно сделать как можно конкретнее, поюзать и понять где можно генереализовать)
// - Invent a new alg (Write a paper)
//
// No raw loops -> coding standart
//
// Use libs - Boost and ASL(похоже не развиватеся)
//
// ASL:
// http://stackoverflow.com/questions/6461621/how-to-compile-asl-boost-based-adobe-c-gui-library-on-linux
// http://stackoverflow.com/questions/2179999/c-adobe-source-libraries-impressions - 
// !! https://github.com/stlab/adobe_source_libraries
// Нужны какие-то потчи на буст. http://stlab.adobe.com/asl_readme.html
// http://stackoverflow.com/questions/6397501/how-to-compile-asl-boost-based-adobe-c-gui-library-on-windows-7
//
// Boost:
// Range: http://www.boost.org/doc/libs/1_41_0/libs/range/doc/boost_range.html
// http://stackoverflow.com/questions/13286876/boostrange-iterator-and-boostiterator-range-confusion - есть еще 
//   ссылка внутри, но там скорее к С++11
// Есть еще алгоритмы

#include "projects/view.h"

#define NO_ASL

#ifndef NO_ASL
#  include <adobe/algorithm/find.hpp>
#  include <adobe/algorithm/for_each.hpp>  // ничего не возвращает
#  include <adobe/algorithm/sort.hpp>
#  include <adobe/algorithm/lower_bound.hpp>
#  include <adobe/algorithm/upper_bound.hpp>
#  include <adobe/algorithm/random_shuffle.hpp>
#endif

#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>
#include <boost/bind.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
//#include <boost/bind/placeholders.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*
void PanelBar::RepositionExpandedPanels(Panel* fixed_panel) {
  int fixed_index = GetPanelIndex(expanded_panels_, *fixed_panel);

  const int center_x = fixed_panel->cur_panel_center();
  for (size_t i = 0; i < expanded_panels_.size(); ++i) {
    Panel* panel = expanded_panels_[i].get();

    //
    if (center_x <= panel->cur_panel_center() || i == expanded_panel_.size() - 1) {
      // если попалю сюда, то это в любом случае выход из цикла
      if (panel != fixed_panel) {
        ref_ptr<Panel> ref = expanded_panels_[fixed_index];
        expanded_panels_.erase(expanded_panels_.begin()+fixed_index);
        if (i < expanded_panels_.size()) {
            expanded_panels_.insert(expanded_panels_.begin() + i, ref);
        } else {
            expanded_panels_.push_back(ref);
        }
      }

      break;
    }
    //
  }
}*/

using std::rotate;
using std::stable_partition;
using std::pair;
using std::vector;
using std::ostream;
using std::for_each;
using std::back_insert_iterator;
using std::bind2nd;
using std::less;
using std::cout;
using std::endl;
using std::copy;
using std::string;

using boost::begin;
using boost::end;

using view::operator<<;

namespace {

//struct print
//{
//template<typename T>
void print(const int& t) //const
{
    cout << t << " ";
}
//};

struct Printer {
    //template<typename T>
    void operator()(const int& t) const {
        cout << t << " ";
        //return 0;
    }
};

// Хорошо бы вернуть что-то - новое положение отрезка - [f_new, l_new)
// TODO: почему такое обобщение?
// TODO: похоже есть дыры
template<typename I>
// I models RandomAccessIterator
int /*pair<I, I>*/ slide(I f, I l, I p) {
    if (p < f) rotate(p, f, l);

    // Ветка выполняется!!
    if (l < p) {
        rotate(f, l, p);
        // [p, p+(l-f)) ?
    }

    // TODO: а остальные случаи

    return 0;
}

}

class IntSequence {
private:
    int value;
public:
    IntSequence(int init) : value(init) {}

    int operator()() {
        return value++;
    }
};

template<typename I, typename S>
pair<I, I> gather(I f, I l, I p, S s) {
    return make_pair(stable_partition(f, p, not1(s)),
                     stable_partition(p, l, s)
    );
}

struct employee {
    explicit employee(const char* _last) : last(_last) {}

    string last;
    string first;

    string get_last() const { return last; }
};

ostream& operator<<(ostream& o, const employee& e) {
    o << "L: " << e.last << " ";
    return o;
}

// rotate
// stable_partition
// stable_sort
//
// For sorted:
// lower_bound 
TEST(SeanParent_, NoRawLoops) {
    // TODO: ошибочный ввод
    // first
    {
        int arr[] = {1, 2, 3, 8, 8, 8, 8, 7, 2, 1};
        const int kSize = sizeof(arr) / sizeof(arr[0]);
        vector<int> v;
        v.insert(v.begin(), arr, arr + kSize);
        vector<int>::iterator it = v.begin();
        cout << v;

        size_t f = 3;
        size_t l = 6 + 1;  // [)
        size_t p = kSize - 1;  // )

        slide(it + f, it + l, it + p);

        cout << v;

        f = 5;
        l = kSize - 1;  // [)
        p = 3;  // )

        slide(it + f, it + l, it + p);

        cout << v;
    }
    cout << endl;

    // second
    {
        int arr[] = {1, 2, 3, 8, 8, 8, 8, 7, 2, 1};
        const int kSize = sizeof(arr) / sizeof(arr[0]);
        vector<int> v(arr, arr + kSize);  // можно в констр., можно вставить, можно назначить
        //v.insert(v.begin(), arr, arr + kSize);
        vector<int>::iterator it = v.begin();
        cout << v;

        size_t edge = distance(v.begin(), v.end());
        pair<vector<int>::iterator, vector<int>::iterator> range
            = gather(v.begin(), v.end(), v.begin() + edge, bind2nd(less<int>(), 4));

        cout << v;

        vector<int> tmp;
        copy(range.first, range.second, back_insert_iterator<std::vector<int> >(tmp));
        cout << tmp;

#ifndef NO_ASL
        // NO CHECK
        cout << *adobe::find(v, 8) << endl;
#endif

        //
        // Functors vs bind - http://stackoverflow.com/questions/17810018/functors-vs-stdbind
        /// Work
        //boost::for_each(boost::make_iterator_range(v.begin(), v.begin()+4) ,print());
        //
        /// Not work with functors
        // F - ConvertibleToFunction?
        // http://stackoverflow.com/questions/9453380/iterating-over-a-stdmap-using-boostbind
        // http://stlab.adobe.com/group__for__each.html
        // Указатель на функция передается, но объект нет.
        //adobe::for_each(make_pair(v.begin(), v.begin()+4), Printer());//&print); // With ptr work
        // boost::peaceholder::_1
        // http://stackoverflow.com/questions/356950/c-functors-and-their-uses
        //
        // Boost.Bind
        // http://www.boost.org/doc/libs/1_55_0/libs/bind/bind.html
        //adobe::for_each(v.begin(), v.begin()+4, &Printer::operator());


        /*
        IntSequence seq(1);
        // частичной специялизации похоже нет
        //generate_n<insert_iterator<vector<int> >, int, IntSequence&>(v.begin(), 4, seq);
        generate_n<vector<int>::iterator, int, IntSequence&>(v.begin(), 4, seq);
        cout << v;

        generate_n<vector<int>::iterator, int, IntSequence&>(v.begin(), 4, seq);
        cout << v;
        */
    }
    cout << endl;

    // lower_bound
    // http://stackoverflow.com/questions/12968498/compare-function-in-lower-bound
    // http://stackoverflow.com/questions/8741065/test-lower-bounds-return-value-against-the-end-iterator
    //
    // The function uses its internal comparison object (key_comp) to determine this,
    // returning an iterator to the first element for which key_comp(element,val) would return false.
    {
        int arr[] = {1, 2, 3, 8, 8, 8, 8, 7, 2, 1};
        vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));

        vector<int> tmp = v;

#ifndef NO_ASL
        adobe::stable_sort(tmp);

        cout << tmp;

        vector<int> range_;

        // возвращает итератор на элемент не меньше значения value - elem >= value
        cout << *adobe::lower_bound(tmp, 2) << endl;
        cout << *std::lower_bound(begin(tmp), end(tmp), 6) << endl;

        // elem > value
        cout << *adobe::upper_bound(tmp, 7) << endl;

        /// Danger:
        // https://www.securecoding.cert.org/confluence/display/cplusplus/ARR34-CPP.+Use+Valid+Iterator+Ranges
        // val_lower <= val_upper
        // TODO: расстояние может быть отрицательным?
        //assert(distance(adobe::lower_bound(tmp, 7), adobe::upper_bound(tmp, 2)) >= 0);

        // Можно передать пару!!
        adobe::copy(make_pair(adobe::lower_bound(tmp, 2), // may be include
         adobe::upper_bound(tmp, 7)), // ) итератор указывает на > 7, и мы его не включаем в копирование
         back_insert_iterator<vector<int> >(range_));
        cout << range_;
#endif
    }

    // Chrome
    {
        // Похоже суть перенести фиксированную панель ближе к началу
        int arr[] = {1, 2, 3, 123, 8, 8, 8, 117, 2, 1};
        vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
        vector<int> expanded_panels_ = v;
        cout << v;

        {
            int fixed_index = 7;
#ifndef NO_ASL
            vector<int>::iterator p = adobe::find(expanded_panels_, 123);//2); похоже предусловия не такие
            vector<int>::iterator f = begin(expanded_panels_) + fixed_index;
            assert(p != expanded_panels_.end());
            assert(p <= f);
            // итераторы портяться, но расстояние останется
            int delta = distance(expanded_panels_.begin(), p);

            int ref = expanded_panels_[fixed_index];
            expanded_panels_.erase(f);  // что-то сдало не активно

            cout << expanded_panels_;

            expanded_panels_.insert(expanded_panels_.begin() + delta, ref);
            cout << expanded_panels_;
#endif
        }

        // rotate version
        {
#ifndef NO_ASL
            expanded_panels_ = v;
            int fixed_index = 7;

            vector<int>::iterator f = begin(expanded_panels_) + fixed_index;
            vector<int>::iterator p = adobe::find(expanded_panels_, 123);//2); похоже предусловия не такие

            assert((p <= p+1) && (p+1 <= f+1));
            //rotate(p, p+1, f+1);
            rotate(p, f, f+1);  // не правильно - на самом деле смотря что нужно
            cout << expanded_panels_;  // не эквивалентно!
#endif
        }

    }

    // use libraries
    {
        // Boost, ASL
        //
        // Have many variants of simple, common algorithm such as find() and copy()
        //
        // Interface symetry
        {
            vector<employee> v;
            v.push_back(employee("Lugansky"));
            v.push_back(employee("Barbar"));
            v.push_back(employee("Parent"));
            v.push_back(employee("Parent"));
            v.push_back(employee("Parent"));
            v.push_back(employee("Yeng"));
#ifndef NO_ASL
            adobe::random_shuffle(v);

            // сортируем и ищем
            // DANGER: не согласованный интерфейс. BAD!!
            //adobe::sort(v, [](const employee& e0, const employee& e1) { return e0.last < e1.last; });
            //auto a = adobe::lower_bound(v, "Parent", [](emp, !!!string) { return e.last < string; };
            adobe::sort(v, less<string>(), &employee::get_last);  // можно и &employee::last
            // auto p =
            cout << *adobe::lower_bound(v, "Parent", less<string>(), &employee::get_last);
            cout << endl;
            // Норм, но лучше сделать с getter
            cout << v;
#endif
        }

        // Далать тело for_each как можно меньше
    }
}
