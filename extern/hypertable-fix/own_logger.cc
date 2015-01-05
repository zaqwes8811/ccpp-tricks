#define GPATCH_SIMPLE_LOGGER

#include <hypertable-fix/own_logger.h>
#include <boost/thread/mutex.hpp>

//namespace loggers {
// LOGloggers::logToFile((msg), std::string(__FILE__), loggers::IntToStr(__LINE__));  \
//}  // space

//namespace loggers {
void logToFile(std::string msg, std::string codeFile, std::string line);

/*
template <typename T>
std::string IntToStr(T tmp) {
  std::ostringstream out;
  out << tmp;
  return out.str();
}
*/
static const char* kPathToLogs = "logs/";
static boost::mutex s_mtx;
void logToFile(std::string msg, std::string codeFile, std::string line) {
  time_t seconds = time(NULL);
  tm* timeinfo = localtime(&seconds);
  char buffer [80];

  // http://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
  strftime(buffer, 80, " %x - %I:%M%p ", timeinfo);
  std::string value = "INFO: " + msg + std::string(buffer)
    + " In file: " + codeFile + ": " + line + "\n";

  boost::mutex::scoped_lock _(s_mtx);
  FILE *h = fopen("./log.log","at+");
  assert(h);
  fwrite(value.data(), sizeof(char), value.length(), h);
  fclose(h);

  // FIXME: bad it!
  std::cout << value;

}


//}
