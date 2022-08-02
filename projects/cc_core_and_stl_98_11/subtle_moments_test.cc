

#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

TEST(Stl, EqAndEq) {
  // равенство не тоже самое что эквивалентность - см. в мейсере 173
  //   find and std::insert
  // для хэш таблиц своя тема с равенством и эквив.

  // Effe. STL - 19
  // "Два объекта х и у считаются эквивалентными по отношению к порядку
  // сортировки, используемому ассоциативным контейнером с, если ни один из них
  // не предшествует другому в порядке сортировки с."

  // http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-7-of-n
  // "save sorted order"

  int w1 = 0;
  int w2 = 1;

  bool is_equal = !(w1 < w2) && !(w2 < w1);

  // better equal
  // std::e

  // op < // good
  // op <= // BAD  x comp x must be FALSE
}

TEST(STL, BackInserterBug) {
  // std_own_ext::compact - have bug
  // *back = ;  // ++back to, but! ++back explicit have no effect
}
