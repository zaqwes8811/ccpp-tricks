// Sutter:
// http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
// DANGER: Хм, премешенный лог...
//
// Qt and C++11 http://qt-project.org/forums/viewthread/28185
//
// Вроде бы и в новом стардарте фич не достаточно для эфф. распараллеливания. 
// (http://tech.yandex.ru/events/yagosti/cpp-user-group/talks/1795/ )

#include <iostream>

#include "tbb/task_scheduler_init.h"
#include "tbb/task.h"

#include <gtest/gtest.h>

namespace {
  
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


// No locks, thread -> task
TEST(SeanParent, NoRawSync) 
{
  // async
  // Libs:
  // PPL(MS), libdispatch(Apple), TBB
}

TEST(TBB, AsyncTry) 
{
  //ParallelFib(25);
}