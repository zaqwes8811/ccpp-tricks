#ifndef SERVICE_CROSS_CUTTINGS_H
#define SERVICE_CROSS_CUTTINGS_H

#include <sstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <ctime>


namespace crosscuttings {
template <typename T>
std::string IntToStr(T tmp) {
    std::ostringstream out;
    out << tmp;
    return out.str();
}

#ifndef GPATCH_SIMPLE_LOGGER
void InitLogger();
#else
void logToFile(std::string msg, std::string codeFile, std::string line);
#endif
}

#ifdef GPATCH_SIMPLE_LOGGER
#define LOG_I(msg) { \
    crosscuttings::logToFile((msg), std::string(__FILE__), crosscuttings::IntToStr(__LINE__));  \
    }
#else
  // glog
  #define LOG_I(msg) { LOG(INFO) << (msg);}
#endif
#endif //SERVICE_CROSS_CUTTINGS_H
