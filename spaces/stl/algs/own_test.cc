
#include "visuality/view.h"

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <numeric>  // partial sum

using namespace std;
using namespace view;

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