
#include <gtest/gtest.h>
#include <boost/thread.hpp>

using boost::thread;

// http://stackoverflow.com/questions/4260209/creating-not-copyable-but-movable-objects-in-c
// thread - movable
class callable {  // must be copyable
public:
  callable() {}  // step 1
  void operator()() {  // можно и с аргументами
    // boost::this_thread::disable_interruption di;  // можно запрещать и разреашать прерывание потока

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


TEST(Parallel, ExecutionExceptionsAndInterraption) {
  f();
}
