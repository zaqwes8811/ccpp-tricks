
#include "visuality/view.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <numeric>  // partial sum
#include <valarray>
#include <vector>

using namespace std;
using namespace view;

TEST(stl, reduce) {

}

/// Numeric
TEST(STL, InclusiveScan) {
  using std::partial_sum;
  using std::minus;
  using std::rotate;

  vector<int> coll;
  insert_elems(coll, 1, 6);

  vector<int> out;

  // equal inclusive scan
  partial_sum(coll.begin(), coll.end(),
              back_inserter(out));

  // exclusive scan from incl. scan
  //for_each(coll.begin(), coll.end(), bind2nd(minus<int>(), ));  // V1 - don't work
  print_elems(out);

  // V2
  rotate(out.begin(), out.end()-1, out.end());
  if (out.begin() != out.end()) out.front() = 0;  // need add I elem

  print_elems(out);
  assert(out.at(0) == 0);
}

TEST(stl, ExclScan) {

}

// Using stable_partition, but how be with predicate - it must be stateless
//   how check buy mask.
//
// http://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning

// DANGER: length not follow
template<class InputIterator, class OutputIterator>
OutputIterator compact(InputIterator in_first, InputIterator in_last,
                       InputIterator mask_first,
                       OutputIterator out_first) {

  // DANGER: No check precond.

  while (in_first!=in_last) {
    if (*mask_first)
      *out_first = *in_first;

    ++out_first;
    ++in_first;
    ++mask_first;
  }
  return out_first;
}

TEST(STL, OwnCompact) {
  using std::valarray;
  using std::back_inserter;
  using std::back_insert_iterator;
  using std::count;
  using std::random_shuffle;
  using std::vector;
  //using std::rd;

  //TODO: copy by filter C++03. In C++11 copy_if
  // http://stackoverflow.com/questions/11028266/how-to-make-stdvector-from-other-vector-with-specific-filter
  //TODO: copy by mask
  // http://www.cplusplus.com/reference/valarray/mask_array/
  // http://bytes.com/topic/c/answers/137137-valarray-iterators
  // http://en.cppreference.com/w/cpp/numeric/valarray
  vector<int> main_mask(10);
  for (int i=0; i<10; ++i) {
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
  //mask.assign()
  valarray<int> foo(10);

  // not compiled
  //foo *= std::valarray<int>(10,5);  //  0 10  2 30  4 50  6 70  8 90
  foo[!mask] = 0;                     //  0 10  0 30  0 50  0 70  0 90

  // remove_copy_if ...
  // to complex...

  // Version 2:
  //compact
  //back_insert_iterator ins = back_inserter(mask1);
  // http://stackoverflow.com/questions/1128535/stl-vector-reserve-and-copy
  // http://stackoverflow.com/questions/4732999/how-does-back-inserter-work
  // http://stackoverflow.com/questions/19583708/should-i-reserve-memory-when-using-stdback-inserter
  int active_elems_count = //main_mask.count(1);  // похоже только в ассоц.
      count(main_mask.begin(), main_mask.end(), 1);
  vector<int> dist;

  dist.reserve(active_elems_count);

  compact(src.begin(), src.end(), main_mask.begin(), back_inserter(dist));
  assert(dist.size() == active_elems_count);
}

struct op {
  bool operator()(int elem, bool mask_elem) {
    return mask_elem;
  }
};

TEST(Own, CompactOnSearch) {
  vector<int> mask(10);
  for (int i=0; i<10; ++i) {
    mask[i] = i % 2;
  }

  vector<int> src(10);
  for (int i = 0; i < 10; ++i) src[i] = i;  //  0  1  2  3  4  5  6  7  8  9

  vector<int> dist;  // FIXME: reverse 

  // Work
  //search()  // ищет последовательность - тут не тот случай - NOT WORK
}

// copy_if right impl!! Meyser Eff. STL 34

