
#include <gtest/gtest.h>
#include <boost/thread.hpp>

using boost::thread;

// http://stackoverflow.com/questions/4260209/creating-not-copyable-but-movable-objects-in-c
// thread - movable
class callable {
public:
  callable() {}  // step 1
  void operator()() {
    return;
  }
private:
  //callable& operator=(const callable& val);  // not protect
  //callable(const callable& r);  // step 1  // this protect
};

static boost::thread copies_are_safe() {
  callable x;
  return boost::thread(x);  // create copy
}

void f()
{
  boost::thread some_thread=copies_are_safe();
  some_thread.join();
}


TEST(Parallel, MutexBase) {
  f();
}
