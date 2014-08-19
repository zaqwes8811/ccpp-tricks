
// TBB Ref. Man. - https://software.intel.com/en-us/node/506045
//
// Task based parallelizm - https://software.intel.com/ru-ru/node/506100

#include <iostream>

#include "tbb/task_scheduler_init.h"
#include "tbb/task.h"

#include <gtest/gtest.h>

namespace {
using namespace tbb;

long CutOff = 4;

long SerialFib( long n ) {
    if( n<2 )
        return n;
    else
        return SerialFib(n-1)+SerialFib(n-2);
}

class FibTask: public task {
public:
    const long n;
    long* const sum;
    FibTask( long n_, long* sum_ ) :
        n(n_), sum(sum_)
    {}
    task* execute() {      // Overrides virtual function task::execute
        if( n<CutOff ) {
            *sum = SerialFib(n);
        } else {
            long x, y;
            FibTask& a = *new( allocate_child() ) FibTask(n-1,&x);
            FibTask& b = *new( allocate_child() ) FibTask(n-2,&y);
            // Set ref_count to 'two children plus one for the wait".
            set_ref_count(3);
            // Start b running.
            spawn( b );
            // Start a running and wait for all children (a and b).
            spawn_and_wait_for_all(a);
            // Do the sum
            *sum = x+y;
        }
        return NULL;
    }
};



long ParallelFib( long n ) {
    long sum;
    FibTask& a = *new(task::allocate_root()) FibTask(n,&sum);
    task::spawn_root_and_wait(a);
    return sum;
}
} // anon. names.


// No locks, thread -> task
TEST(SeanParent, NoRawSync) 
{
  // async
  // Libs:
  // PPL(MS), libdispatch(Apple), TBB
}

TEST(TBB, AsyncTry) 
{
  ParallelFib(25);
}