#include <thread>

#include <boost/thread.hpp>

// FIXME: use boost::thread. Need rebuild boost and libstdc++?
// http://boost.2283326.n4.nabble.com/clang-3-6-thread-sanitizer-complains-on-shared-ptr-operations-td4671416.html
// Races not founded
//
// readelf -d a.out | grep NEEDED
// FIXME: may be wring linking?

void f(int& X) {
  X = 42;
  printf("hello");
}

int main() {
    int X;
    // not working
    boost::thread t(boost::bind(&::f, boost::ref(X)));
    //std::thread t1([&] { X = 44; });
    X = 43;
    t.join();
    //t1.join();
}
