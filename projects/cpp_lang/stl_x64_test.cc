// https://software.intel.com/en-us/forums/topic/534769

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <list>
#include <vector>

#include <cassert>

using namespace std;

// http://stackoverflow.com/questions/7927764/specializing-iterator-traits
// My bads!
class BigPtrDiff {
public:
};

// FIXME: special iterator for very big arrays

namespace refer {

// FIXME: if diff_type - ptrdiff_t -> 1/2 size -> overflow
template <class InputIt, class T>
typename iterator_traits<
    InputIt>::difference_type // may be 128 size or something
count(InputIt first, InputIt last, const T &value) {
  typename iterator_traits<InputIt>::difference_type ret = 0;
  for (; first != last; ++first) {
    if (*first == value) {
      ret++; // FIXME: what happened if ++ size_t/2
    }
  }
  return ret;
}
} // namespace refer

TEST(STL, Strange) {
  vector<char> mask(10);
  for (int i = 0; i < 10; ++i)
    mask[i] = i % 2;

  // FIXME: why return diff type?
  // http://stackoverflow.com/questions/7505083/why-does-the-c-standard-algorithm-count-return-a-ptrdiff-t-instead-of-size-t
  // http://stackoverflow.com/questions/12573377/why-do-stdcount-if-return-iteratordifference-type-instead-of-size-t
  auto activeCount =
      count(mask.begin(), mask.end(), 1); // FIXME: can get only half?

  EXPECT_TRUE(sizeof(ptrdiff_t) == sizeof(size_t));

  // ptrdiff_t -> size_t -> overflow!
  // auto r = mask[-1];  // ASan - heap-buffer-overflow
  // auto r = mask[ptrdiff_t(-1)];  // ASan - heap-buffer-overflow

  vector<int> dst;
  int a[10];

  // http://www.codeproject.com/Articles/60082/About-size-t-and-ptrdiff-t
  dst.size() == activeCount;

  // http://stackoverflow.com/questions/6741718/size-t-ptrdiff-t-and-stdvectorsize
  ptrdiff_t t = std::numeric_limits<size_t>::max();
  cout << hex << std::numeric_limits<size_t>::max() << endl;

  // looks work?
  cout << hex << (size_t)(std::numeric_limits<ptrdiff_t>::max() + 2) << endl;

  // https://groups.google.com/forum/#!topic/comp.std.c/UxmPRmty-LQ%5B1-25%5D
  cout << dec << t << endl;

  // impl max size even < half of size_t
  cout << hex << dst.max_size() << " : Max vector size" << endl;
  cout << hex << " " << std::list<int>().max_size() << " : Max list size"
       << endl;
  cout << hex << std::numeric_limits<ptrdiff_t>::max()
       << " : Max ptrdiff_t size" << endl;
  cout << hex << std::vector<char>().max_size() << " : Max vector<char> size"
       << endl;

  auto tt = std::count(a, a + 10, 1);

  tt == activeCount;

  // if dist(m.begin(), end()) > max ptrdiff_t => UB!
  // Need check ranges
  // http://bytes.com/topic/c/answers/603839-mixing-signed-unsigned
}

TEST(Stlx64, Intel) {
  // https://software.intel.com/en-us/forums/topic/534769
  // "Why does the STL uses size_t and not ptrdiff_t for array indexing ?"

  // http://blogs.msdn.com/b/david_leblanc/archive/2008/09/02/ptrdiff-t-is-evil.aspx

  // http://stackoverflow.com/questions/7956763/variables-of-type-size-t-and-ptrdiff-t
  // if signed => size if 1/2

  int a[10] = {0}, *p = a + 3, &r = p[-1];

  // Neg is cycle access as in python

  // http://cpgotchas.blogspot.ru/2008/02/sizet-ptrdifft-and-offt.html

  // ISO:
  // http://en.cppreference.com/w/cpp/types/ptrdiff_t
}
