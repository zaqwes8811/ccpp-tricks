// STL not check errors at most - precond check user
//
// range must be correct [first, last) first befor last -
//   for copy() at last
//
// find return last iter if not found

#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

using std::vector;
using std::copy;

TEST(Sutter, STLTest) {
  // it1 = find
  // it2 = find

  // ...
  // e.insert()  // может сделать итератры недействительными
  // iters can be dangling
  //copy(it1, it2 ...)  //
}

// p. 76
TEST(Sutter, CToCppJump) {
  vector<char> v;
  v.push_back('a');

  //TODO: what if empty?
  // При перераспределении указатель стан. не корректен
  char* p = &v[0];
}
