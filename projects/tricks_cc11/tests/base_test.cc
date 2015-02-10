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

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

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
