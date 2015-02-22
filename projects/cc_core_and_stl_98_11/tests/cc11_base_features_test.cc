#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

TEST(Lava, Alg) {
  int myints[] = {10,20,30,30,20,10,10,20};
  vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  // http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-7-of-n
  // really use for search
  sort(v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  // but! find nearst
  bool contain = std::binary_search(v.begin(), v.end(), 20);
  auto low = std::lower_bound(v.begin(), v.end(), 20);
  std::cout << "at position " << (low - v.begin()) << '\n';
  auto up = std::upper_bound(v.begin(), v.end(), 20);
  vector<int> slice(low, up);
  for_each(slice.begin(), slice.end(), [] (int e) { cout << e << " "; });
  cout << endl;

  // Совет 45. Различайте алгоритмы count, find, - крит равенства
  // binary_search, lower_bound, upper_bound и equal_range - критерий эквил
}
