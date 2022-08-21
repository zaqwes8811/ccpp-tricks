// STL not check errors at most - precond check user
//
// range must be correct [first, last) first befor last -
//   for copy() at last
//
// find return last iter if not found

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using std::copy;
using std::vector;

TEST(Sutter, STLTest) {
    // it1 = find
    // it2 = find

    // ...
    // e.insert()  // может сделать итератры недействительными
    // iters can be dangling
    // copy(it1, it2 ...)  //
}

// p. 76
TEST(Sutter, CToCppJump) {
    vector<char> v;
    v.push_back('a');

    // TODO: what if empty?
    //  При перераспределении указатель стан. не корректен
    char *p = &v[0];
}
