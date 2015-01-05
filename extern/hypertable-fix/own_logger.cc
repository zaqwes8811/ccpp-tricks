#define GPATCH_SIMPLE_LOGGER

#include <hypertable-fix/own_logger.h>
#include <boost/thread/mutex.hpp>

namespace crosscuttings {
//static const char* kPathToLogs = "logs/";

#ifndef GPATCH_SIMPLE_LOGGER
//using namespace ::google;
//void InitLogger() {
//   //google::InitGoogleLogging(argv[0]);
//   InitGoogleLogging("random");
//
//   for (LogSeverity s = google::GLOG_WARNING; s < NUM_SEVERITIES; s++)
//     SetLogDestination(s, "");
//   SetLogDestination(GLOG_INFO, kPathToLogs);
//}
#else
static boost::mutex g_loggerMutex;
void logToFile(std::string msg, std::string codeFile, std::string line) {
  time_t seconds = time(NULL);
  tm* timeinfo = localtime(&seconds);
  char buffer [80];

  // http://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
  strftime(buffer, 80, " %x - %I:%M%p ", timeinfo);
  std::string value = "INFO: " + msg + std::string(buffer)
    + " In file: " + codeFile + ": " + line + "\n";
  {
    boost::mutex::scoped_lock _(g_loggerMutex);
    FILE *log_file = fopen("./log.log","at+");
    assert(log_file);
    fwrite(value.data(), sizeof(char), value.length(), log_file);
    fclose(log_file);
    std::cout << value;
  }
}
#endif
}
