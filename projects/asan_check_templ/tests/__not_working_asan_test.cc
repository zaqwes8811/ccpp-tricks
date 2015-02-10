#include "heart/config.h"

#include <gtest/gtest.h>

// FIXME: not see it!!

int* g;

// ASAN_OPTIONS=detect_stack_use_after_return=1
namespace {
void LeakLocal() {
  int local;
  g = &local;
}

int* get() {
  int local;
  return &local;
}
}

int r() {
  int i = *get();
  LeakLocal();
  return *g;
}

namespace {
int global_array[100] = {-1};

int m(int argc) {
  return global_array[argc+100];
}
}

TEST(ASanTest, Mem)
{
  //int *a = new int[100];
  //delete[] a;
  //int b =
      //return a[9];
  //int k = *get();
  //return k+100;
  //std::vector<int> r;
  //r.reserve(90);
  //return r[9];
  int k = r();
  k++;
  k = m(4);
  k--;
}
