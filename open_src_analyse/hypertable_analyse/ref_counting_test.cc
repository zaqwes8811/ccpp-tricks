

#include <gtest/gtest.h>

#include <boost/intrusive_ptr.hpp>


//#include "Common/ReferenceCount.h"

// As a general rule, if it isn't obvious whether intrusive_ptr better fits 
//  your needs than shared_ptr, try a shared_ptr-based design first.
//
// Cons:
//   нет weak-пары
TEST(Ref, BoostIntr) {
  
}

// https://code.google.com/p/chromiumembedded/wiki/UsingTheCAPI

// зачем наследовать?