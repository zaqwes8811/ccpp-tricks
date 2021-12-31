#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

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

// Crosscompilation:
// http://stackoverflow.com/questions/20574808/how-to-check-arm-none-linux-gnueabi-g-support-for-c11
// http://blog.worldofcoding.com/2014/05/cross-compiling-c11-without-going-madder.html
//
// С++11 не совместим с C++03. А с C++98?
//
// Move in
// http://stackoverflow.com/questions/3106110/what-is-move-semantics
// http://blog.smartbear.com/c-plus-plus/the-biggest-changes-in-c11-and-why-you-should-care/
// http://lin-techdet.blogspot.ru/2013/03/c11-rvalue.html
// !!!https://cloudtips.org/introduction-to-rvalue-references.html
//
// http://sergeyteplyakov.blogspot.ru/2012/05/c-11-faq.html
namespace {
// Cpp-Seasoning - где нужно move - не очень то где - конструктор и assign
// "Some sink.."
// http://stackoverflow.com/questions/18203201/is-the-introduction-of-rvalue-references-actually-useful
// http://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11/5481588#5481588

// http://en.wikipedia.org/wiki/C++11#Explicitly_defaulted_and_deleted_special_member_functions
//
// Move assign and ctor:
//   http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
//   http://en.cppreference.com/w/cpp/language/move_constructor
//   http://msdn.microsoft.com/en-us/library/dd293665.aspx
//  http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html !!
//
// Old:
// Default constructor
// Copy constructor
// Copy assignment operator
// Destructor
//
// TODO: компилятор как-то различает lvalue from rvalue?
// http://meetingcpp.com/index.php/br/items/c1y-move-copy-destructors.html
class MemoryPage {
  MemoryPage(MemoryPage&& other)
  //: size(0), buf(nullptr)
  {
  // pilfer other’s resource
  //size=other.size;
  //buf=other.buf;

  /// DANGER: reset other - опустошает агрументы!!
  // TODO: А как быть деструктору?
  //other.size=0;
  //other.buf=nullptr;
}

private:
  MemoryPage& operator=(MemoryPage&& other) = default;

};

// Еще что-то про uniaue_ptr http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=495

} // anon. names.

// http://www.artima.com/cppsource/rvalue.html

TEST(Cpp11, SimpleLambda) {
  std::vector<int> someList;
  int total = 0;
  std::for_each(someList.begin(), someList.end(), [&](int x) {
    total += x;
  });
}

TEST(Cpp11, Lava) {
  // http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-9-of-n
  //std::move()
  //std::forward

  //RVal -> move sem  - more effintion without change code symantic
  //    -> perfect forwarding - for libs

  // LVal - has name - can make &
  // lref - it alias
  // RVal - no name - &172 - no! &(x+y) - no!
  // string&& rr = s + t;  - bad! only example - not use it!
  // X&& foo() - very bad!!!
  //
  // Temp T -> Yes const T& -> No T&
  //
  // If name => lval - need treat as rval -> std::move() l -> r
}

// Forwarding
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2002/n1385.htm
// http://stackoverflow.com/questions/7257144/when-to-use-stdforward-to-forward-arguments
// http://habrahabr.ru/post/226229/
class wrapper_base { };

template<class T> class wrapper: public wrapper_base
{
private:

    T t_;

public:

    // forwarding constructors

    wrapper(): t_() {}
    wrapper(int a1): t_(a1) {}
    wrapper(int a1, int a2): t_(a1, a2) {}
    // ...

};

template<class T> std::auto_ptr<T> auto_new()
{
    return std::auto_ptr<T>(new T());
}

template<class T> std::auto_ptr<T> auto_new(int a1)
{
    return std::auto_ptr<T>(new T(a1));
}

template<class T> std::auto_ptr<T> auto_new(int a1, int a2)
{
    return std::auto_ptr<T>(new T(a1, a2));
}

// const and non const troubles
// (!!!!) http://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/
template <class T>
void func(T&& t) {
}
//Don't let T&& fool you here - t is not an rvalue reference [2]. When it appears in a
//type-deducing context, T&& acquires a special meaning.

// http://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

