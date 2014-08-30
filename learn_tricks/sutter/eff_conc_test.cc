// Eff conc.
// http://herbsutter.com/2009/11/11/effective-concurrency-prefer-structured-lifetimes-%E2%80%93-local-nested-bounded-deterministic/

#include <gtest/gtest.h>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

// TODO: Use Threads Correctly = Isolation + Asynchronous Messages
// http://www.drdobbs.com/parallel/use-threads-correctly-isolation-asynch/215900465

// TODO: Use Thread Pools Correctly: Keep Tasks Short and Nonblocking
// http://stackoverflow.com/questions/19500404/how-to-create-a-thread-pool-using-boost-in-c
//
// http://thisthread.blogspot.co.il/2011/04/multithreading-with-asio.html
namespace
{
  boost::mutex mio; // 1
 
  void logMsg(char* reason, int i)
  {
    boost::lock_guard<boost::mutex> lock(mio); // 2.
    std::cout << reason << " for " << i << " at " << std::time(0) << std::endl;
  }
 
  void jobOne(int secs) // 3.
  {
    logMsg("Start jobOne", secs);
    boost::this_thread::sleep(boost::posix_time::millisec(1000 * secs));
    logMsg("End jobOne", secs);
  }
 
  void jobTwo(int millisecs)
  {
    logMsg("Start jobTwo", millisecs);
    boost::this_thread::sleep(boost::posix_time::millisec(millisecs));
    logMsg("End jobTwo", millisecs);
  }
}

// Pools
//   http://thisthread.blogspot.co.il/2011/04/multithreading-with-asio.html
//   http://stackoverflow.com/questions/16677287/boostthreadpoolpool-vs-boostthread-group
//   http://stackoverflow.com/questions/19500404/how-to-create-a-thread-pool-using-boost-in-c
//   http://techiesaint.wordpress.com/2012/12/16/implementing-threadpool-pattern-in-c-using-boostthread-pool/
//   http://www.tonicebrian.com/2012/05/23/thread-pool-in-c/