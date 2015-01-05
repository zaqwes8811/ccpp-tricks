
#define BOOST_THREAD_PROVIDES_FUTURE

#include <gtest/gtest.h>
#include <boost/thread/future.hpp>

#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

class MyException : public std::runtime_error {
public:
  MyException(const char* m) : std::runtime_error(m) { }
};

int throwed()
{
  // wrap to std::exception
  //throw 42;
  throw MyException("hello");
}

TEST(BoostFuture, Exception) {
  boost::packaged_task<int> pt(throwed);
  boost:: future<int> fi=pt.get_future();

  boost::thread task(boost::move(pt)); // launch task on a thread

  fi.wait(); // wait for it to finish

  //assert(fi.is_ready());
  //assert(fi.has_value());
  assert(fi.has_exception());
  try {
    fi.get();
  } catch (std::exception& e) {
    cout << e.what() << endl;
  }
  //assert(fi.get_state()==boost::future_state::ready);
  //assert(fi.get() == 42);

}
