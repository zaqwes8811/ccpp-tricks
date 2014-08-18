// About:
// http://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap?rq=1
//
// http://stackoverflow.com/questions/147298/multithreaded-memory-allocators-for-c-c
// http://stackoverflow.com/questions/1381078/parallel-reads-from-stl-containers?rq=1
//
// Options:
//   http://code.google.com/p/gperftools/
//   http://stackoverflow.com/questions/2158196/multithreaded-heap-management
//   Intel TBB - http://www.threadingbuildingblocks.org/docs/help/tbb_userguide/Memory_Allocation.htm#tutorial_Memory_Allocation

#include <vector>
#include <iostream>

// 3rdparty::common
#include <tbb/scalable_allocator.h>


int main() {
  
  /// Intel TBB
  std::vector<int, tbb::scalable_allocator<int> > v;
  
  return 0;
}