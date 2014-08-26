// Guide:
//   https://software.intel.com/en-us/articles/intel-guide-for-developing-multithreaded-applications
//   !! https://software.intel.com/ru-ru/node/506045
// 
// Design patterns:
//   https://software.intel.com/ru-ru/node/506112
//
// Parallel DS:
//   http://www.threadingbuildingblocks.org/docs/help/tbb_userguide/concurrent_hash_map.htm


#include <cassert>
#include <ostream>

#include <gtest/gtest.h>

#include "tbb/task_scheduler_init.h"
#include "tbb/task.h"
#include "tbb/concurrent_hash_map.h"

using namespace tbb;
using namespace std;

namespace {
typedef concurrent_hash_map<int, int> TaskTable;
  
long SerialFib(long n) {
  if (n < 2)
    return n;
  else 
    return SerialFib(n-1)+SerialFib(n-2);
}

const long CutOff = 4;

class FibTask : public task {
public:
  const long n;
  long* const sum;
  FibTask(long n_, long* sum_)
    : n(n_), sum(sum_) 
  {}
  
  task* execute() {
    // Если решена то вернуть результат
    
    if (n < CutOff) {
      *sum = SerialFib(n);
    } else {
      long x = 0;
      long y = 0;
      FibTask& a = *new(allocate_child()) FibTask(n-1, &x);
      FibTask& b = *new(allocate_child()) FibTask(n-2, &y);
      
      // DANGER: 
      set_ref_count(3);  // not global - it's member
      
      // Starts
      spawn(b);
      spawn_and_wait_for_all(a);  // похоже тоже метод
      
      // Do sum
      *sum = x+y;
      
      // сохраняем результат в хэштаблице
    }
    return NULL;
  }
};

long ParallelFib(long n) {
  long sum;
  FibTask& a = *new(task::allocate_root()) FibTask(n, &sum);
  task::spawn_root_and_wait(a);
  return sum;
}
}

TEST(TBB, ParallelFibNoDynPro) {
  long n = 4;//38;
  long r = ParallelFib(n);
  //assert(r == 39088169);
  
  {
    // http://stackoverflow.com/questions/23501591/tbb-concurrent-hash-map-find-insert
    // http://www.threadingbuildingblocks.org/docs/help/reference/containers_overview/concurrent_hash_map_cls.htm
    // Похоже интерфейс не такой как у stl-like versions
    TaskTable task_table;
  }
  
}