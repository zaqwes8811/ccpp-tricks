
#include "projects/std_own_ext.h"

#include <gtest/gtest.h>

#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

// diff. remove policy
namespace meow {
namespace detail {
// machinery - util
// calc on compilations - overload, ...
struct vectorlike_tag {};
struct listlike_tag {};
struct associative_tag {};

template <typename C> struct container_traits; // FIXME: forward decl.?

template <typename T, typename A> struct container_traits<std::vector<T, A>> {
  typedef vectorlike_tag category;
};

template <typename T, typename A> struct container_traits<std::deque<T, A>> {
  typedef vectorlike_tag category;
};

template <typename T, typename A> struct container_traits<std::list<T, A>> {
  typedef listlike_tag category;
};

template <typename T, typename A> struct container_traits<std::set<T, A>> {
  typedef associative_tag category;
};

// helpers
template <typename Container, typename X>
void erase_helper(Container &c, const X &x, vectorlike_tag) {
  c.erase(std::remove(c.begin(), c.end(), x), c.end());
}
} // namespace detail

// really
template <typename Container, typename X>
void erase_helper(Container &c, const X &x) {
  detail::erase_helper(
      c, x, typename detail::container_traits<Container>::category());
}
} // namespace meow

// http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-3-of-n
TEST(Lava, HW1) {
  // erasing
}

TEST(Lava, L3_ptrs) {
  unique_ptr<int> up(new int(8));  // user &&
  unique_ptr<int> up3(new int(8)); // user &&

  // move resources - up - empty!
  unique_ptr<int> up2 = std::move(up);

  up3 = std::move(up2);

  assert(!up);
}
