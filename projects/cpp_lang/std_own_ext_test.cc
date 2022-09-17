// cotainer <- glue_iter <- algor.
//
// используя итераторы можно на основе контейнеров делать свои алгоритмы
//
//
// Sean Paretn Ch9 - Seasoning
//
#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>  // partial sum
#include <valarray>
#include <vector>

#include "common/std_own_ext_v2.h"
#include "common/view.h"

using namespace std;
using namespace view;

using std_own_ext::compact;

TEST(STL, InclusiveScan) {
    vector<int> coll;
    insert_elems(coll, 1, 6);

    vector<int> out;

    // equal inclusive scan
    partial_sum(coll.begin(), coll.end(), back_inserter(out));
}

TEST(stl, ExclScan) {
    vector<int> coll;
    insert_elems(coll, 1, 6);

    vector<int> out;

    // equal inclusive scan
    partial_sum(coll.begin(), coll.end(), back_inserter(out));

    // exclusive scan from incl. scan
    // for_each(coll.begin(), coll.end(), bind2nd(minus<int>(), ));  // V1 - don't
    // work
    print_elems(out);

    // V2 - т.е. мы просто сдвигаем отсортированный - хрень какая-то
    if (!out.empty()) {
        int I = 0;
        rotate(out.begin(), --out.end(), out.end());  // O(n)?  or O(n^2)
        out.front() = I;                              // need add I elem
    }

    print_elems(out);
    assert(out.at(0) == 0);
}

TEST(STL, OwnCompactDev) {
    // FIXME: copy by filter C++03. In C++11 copy_if
    //  http://stackoverflow.com/questions/11028266/how-to-make-stdvector-from-other-vector-with-specific-filter
    // FIXME: copy by mask
    //  http://www.cplusplus.com/reference/valarray/mask_array/
    //  http://bytes.com/topic/c/answers/137137-valarray-iterators
    //  http://en.cppreference.com/w/cpp/numeric/valarray

    using std::back_insert_iterator;
    using std::back_inserter;
    using std::count;
    using std::random_shuffle;
    using std::valarray;
    using std::vector;

    vector<int> main_mask(10);
    for (int i = 0; i < 10; ++i) {
        main_mask[i] = i % 2;
    }

    random_shuffle(main_mask.begin(), main_mask.end());

    vector<int> src(10);
    for (int i = 0; i < 10; ++i) src[i] = i;  //  0  1  2  3  4  5  6  7  8  9

    // filter
    // Version 1:
    valarray<int> mask(10);
    assert(mask.size() == main_mask.size());
    copy(main_mask.begin(), main_mask.end(), &mask[0]);
    // mask.assign()
    valarray<int> foo(10);

    // not compiled
    // foo *= std::valarray<int>(10,5);  //  0 10  2 30  4 50  6 70  8 90
    foo[!mask] = 0;  //  0 10  0 30  0 50  0 70  0 90

    // remove_copy_if ...
    // to complex...

    // Version 2:
    // compact
    // back_insert_iterator ins = back_inserter(mask1);
    // http://stackoverflow.com/questions/1128535/stl-vector-reserve-and-copy
    // http://stackoverflow.com/questions/4732999/how-does-back-inserter-work
    // http://stackoverflow.com/questions/19583708/should-i-reserve-memory-when-using-stdback-inserter
    ptrdiff_t active_elems_count =  // main_mask.count(1);  // похоже только в ассоц.
        count(main_mask.begin(), main_mask.end(), 1);
    vector<int> dist;

    dist.reserve(active_elems_count);

    compact(src.begin(), src.end(), main_mask.begin(), back_inserter(dist));
    assert(dist.size() == active_elems_count);
}

TEST(STL, OwnCompact) {
    using std::back_insert_iterator;
    using std::back_inserter;
    using std::count;
    using std::random_shuffle;
    using std::vector;

    vector<int> mask(10);
    for (int i = 0; i < 10; ++i) mask[i] = i % 2;
    vector<int> src(10);
    for (int i = 0; i < 10; ++i) src[i] = i;

    // FIXME: why return diff type?
    auto activeCount = count(mask.begin(), mask.end(), 1);

    EXPECT_LT(activeCount, mask.size());

    random_shuffle(mask.begin(), mask.end());

    vector<int> dst
        //;
        (activeCount, 0);

    compact(src.begin(), src.end(), mask.begin(), dst.begin()
            // back_inserter(dist)
    );

    EXPECT_EQ(dst.size(), activeCount);

    // http://www.codeproject.com/Articles/60082/About-size-t-and-ptrdiff-t
    dst.size() == activeCount;
}

struct op {
    bool operator()(int elem, bool mask_elem) { return mask_elem; }
};

TEST(Own, CompactOnSearch) {
    vector<int> mask(10);
    for (int i = 0; i < 10; ++i) {
        mask[i] = i % 2;
    }

    vector<int> src(10);
    for (int i = 0; i < 10; ++i) src[i] = i;  //  0  1  2  3  4  5  6  7  8  9

    vector<int> dist;  // FIXME: reverse

    // Work
    // search()  // ищет последовательность - тут не тот случай - NOT WORK
}

// compact можно сделать через for_each - для нее похоже могут возникать
// побобные эффекты
//  тогда маску можно передать в конструктор (или указатель, со ссылками похоже
//  лучше так не делать) и по ходу вычислять индекс.

// copy_if right impl!! Meyser Eff. STL 34
