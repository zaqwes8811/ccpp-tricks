#ifndef SERVICE_CROSS_CUTTINGS_H
#define SERVICE_CROSS_CUTTINGS_H

#ifdef GPATCH_SIMPLE_LOGGER
    #include <stdio.h>
    #include <ctime>

    #include <sstream>
    #include <string>
#else
    #define GLOG_NO_ABBREVIATED_SEVERITIES
    #include <stdlib.h>
    #include <glog/logging.h>
#endif

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

// Danger!!
// записать в журнал содержимое массива опред. длины,
// начиная с опред. индекса и с аркером полезного заголовка
// перевод в hex
#define LOG_ARRAY(first, length, buffer_name, marker, name) string msg; \
  LOG_I("#"+name) \
  for (int i = (first); i < (length); i++ ) { \
    uchar current = (buffer_name)[i]; \
    string oneRecord; \
    if(i != (marker)) {\
      oneRecord = "["+int2str(i)+"]="+hl(current)+" "; \
    } else { \
      oneRecord = "["+int2str(i)+"]="+hl(current)+" "; \
    } \
    msg += oneRecord; \
    LOG_I(oneRecord) \
  }

// записать в журнал набор строк
#define LOG_V_OF_STR(v_of_s) \
  std::vector<std::string>::iterator end = v_of_s.end(); \
  std::vector<std::string>::iterator at = v_of_s.begin(); \
  for (; at != end; ++at ) { \
    LOG_I(*at) \
  }
#endif //SERVICE_CROSS_CUTTINGS_H
