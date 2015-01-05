#include <gtest/gtest.h>
#include <hypertable-fix/Common/Logger.h>

using namespace Hypertable;

TEST(Hyp, Logger) {
  HT_LOG(Logger::Priority::ALERT, "error");

  Logger::get()->log(Logger::Priority::INFO, "hello");

  (*Logger::get()) << "hello";
}
