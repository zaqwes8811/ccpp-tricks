
// http://www.chromium.org/developers/coding-style/cpp-dos-and-donts#TOC-Stop-inlining-code-in-headers
/**

If you have the class in a header file:

#include "BigImplementationDetail.h"
class PublicInterface {
  public:
    /* ... * /
  private:
    // private! if public need export as interface
    static BigImplementationDetail detail_;
};

You should try to move that from a class member into the anonymous namespace in the implementation file:

namespace {
BigImplementationDetail detail_;
}  // namespace

*/


/**
Stop inlining code in headers
*/


/**
void foo() {
    static int BAD_COUNT = ComputeTheCount();  // THREAD-UNSAFE
    static int GOOD_COUNT = 42;  // C++03 3.6.2 says this is done before dynamic initialization, so probably thread-safe.
}
*/
