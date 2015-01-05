
#define BOOST_THREAD_PROVIDES_FUTURE

#include <gtest/gtest.h>
#include <boost/thread/future.hpp>
#include <hypertable-fix/Common/Logger.h>
#include <boost/exception_ptr.hpp>

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
  //throw MyException("hello");
  try {
    HT_CHECK(false);
  } catch (Hypertable::Exception& e) {
    cout << e << endl;
    throw;
  }
}

// C call mech - no throw
int helper_boundary_c() {
  try {
    // why future? call wrapper can throw to
    // need soo much code!
    //
    // here only std::exception - no app specific!
    //
    // "-":
    //   - only one task
    //   - can throw anyway
    //   - what kind of exception can know only inside task
    boost::packaged_task<int> task(throwed);  // std::bad_alloc
    boost::future<int> fi = task.get_future();
    task();

    // exception unknown here! all info lost
    if (!fi.is_ready() || fi.has_exception())
      return -1;

    int r = fi.get();
    return r;
  } catch(std::exception& e) {
    // runtime errors
    return -1;
  }
}

TEST(BoostFuture, Exception) {
  try {
    // all can throw!! rear but...
    boost::packaged_task<int> pt(throwed);  // std::bad_alloc

    boost::future<int> fi = pt.get_future();

    //boost::thread task(boost::move(pt)); // launch task on a thread
    pt();

    fi.wait(); // wait for it to finish
    assert(fi.is_ready());

    //assert(fi.is_ready());
    //assert(fi.has_value());
    assert(fi.has_exception());
    boost::exception_ptr eptr = fi.get_exception_ptr();
    try {
    //  fi.get();  // can throw own exceptions
      if (eptr) boost::rethrow_exception(eptr);//.rethrow
    } catch (Hypertable::Exception& e) {
      //cout << e << endl;  // not work
    } catch (std::exception& e) {
      // how!!
      cout << e.what() << endl;
    }
    //assert(fi.get_state()==boost::future_state::ready);
    //assert(fi.get() == 42);

    //boost::async()
    boost::future<int> f;
    EXPECT_THROW(f.get(), std::exception);//boost::future_uninitialized);
  } catch (std::exception& e) {
    // heap specific
    // illegal states
    cout << e.what() << endl;
  }
}

TEST(BoostFuture, Boundary) {
  helper_boundary_c();
}
