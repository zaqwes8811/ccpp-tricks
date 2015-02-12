#include <thread>

#include <boost/thread.hpp>

// FIXME: use boost::thread. Need rebuild boost and libstdc++?
// http://boost.2283326.n4.nabble.com/clang-3-6-thread-sanitizer-complains-on-shared-ptr-operations-td4671416.html
// Races not founded
//
// readelf -d a.out | grep NEEDED
// FIXME: may be wring linking?
//
// ldd - all right
/**
linux-vdso.so.1 =>  (0x00007fff9d0fe000)
    libboost_system.so.1.57.0 => /opt/big-3rdparty/boost_1_57_0/clang_libx64/lib/libboost_system.so.1.57.0 (0x00007f762d3a1000)
    libboost_thread.so.1.57.0 => /opt/big-3rdparty/boost_1_57_0/clang_libx64/lib/libboost_thread.so.1.57.0 (0x00007f762d174000)
    libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f762cf3f000)
    librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007f762cd37000)
    libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f762cb33000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f762c82c000)
    libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f762c528000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f762c312000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f762bf4b000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f762ec9c000)

*/

// FIXME: old clang?
// FIXME: gcc?
// FIXME: can't detect

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
