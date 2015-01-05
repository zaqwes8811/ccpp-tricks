#include <gtest/gtest.h>
#include <hypertable-fix/Common/Logger.h>

#include <iostream>

using namespace Hypertable;
using std::endl;
//using Hypertable::operator <<;

TEST(Hyp, Logger) {
  HT_LOG(Logger::Priority::ALERT, "error");

  Logger::get()->log(Logger::Priority::INFO, "hello");

  (*Logger::get()) << "hello HEX:" << std::hex << 10 << endl;
}
