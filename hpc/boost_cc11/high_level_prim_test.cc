// Motivation:
//  Sean Parent - "No raw sync", Sutter, Intel TBB (планеровщик и task based parallelism)
//  Tasks better.
//
// Tut.
//   http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-8-futures-and-promises.html
//

#include <ostream>
#include <vector>

// C++11
#include <future>
#include <thread>

#include <gtest/gtest.h>
 
/// Advanced?
// Barrier
//

// TODO: если что-то вроде планеровщика в future and etc.
// http://stackoverflow.com/questions/14351352/will-asynclaunchasync-in-c11-make-thread-pools-obsolete-for-avoiding-expen

// Async Tasks in C++11: Not Quite There Yet
//   !!http://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/
TEST(TBP, WrongInCpp11) {
  using namespace std;
  cout << "Main id:" << this_thread::get_id() << endl;
  
}