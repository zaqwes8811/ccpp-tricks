// http://www.chromium.org/developers/coding-style#TOC-CHECK-DCHECK-and-NOTREACHED-

#include "hypertable-fix/own_logger.h"

#include <gtest/gtest.h>
#include <hypertable-fix/Common/Logger.h>
#include <hypertable-fix/Common/Error.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Hypertable::Logger::get;
using Hypertable::Logger::Priority::ALERT;
using Hypertable::Logger::Priority::INFO;
//using namespace Hypertable;
using std::endl;
using std::stringstream;
//using Hypertable::operator <<;
using std::string;

void test() {
  //HT_EXPECT(false, Hypertable::Error::SOFT_ASSERT);
  HT_CHECK(!std::vector<char>().empty());
  //HT_THROW(Hypertable::Error::ALREADY_EXISTS, "message");
}

TEST(Hyp, LoggerFromThere) {
  HT_LOGF(ALERT, "\nerror %d", 89);

  //get()->log(INFO, "hello");  // wrong way

  // it's not atomic - need lock
  // how get current line? need macro
  // FIXME: trouble - to much
  {
    // guard _();
    //(*Logger::get()) << "hello HEX:" << std::hex << 10 << endl;
  }

  stringstream s;
  s << "endl" << "ni\n";
  std::cout << s.str();

  try {
    //HT_TRY("hello", test());
    test();
  } catch (Hypertable::Exception& e) {
    stringstream s;
    s << e;//.message();
    HT_LOG(INFO, s.str().c_str());
    //std::cout << s.str() << endl;
  }

  LOG_INFO("hello");
}
