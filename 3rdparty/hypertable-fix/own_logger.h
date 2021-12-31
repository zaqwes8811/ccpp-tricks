#ifndef SERVICE_CROSS_CUTTINGS_H
#define SERVICE_CROSS_CUTTINGS_H

#include <hypertable-fix/Common/Logger.h>

#include <sstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <ctime>

// Deprecated:
#define LOG_INFO(msg) do { \
    HT_LOG(Hypertable::Logger::Priority::INFO, (msg)); \
    } while(0)

#endif //SERVICE_CROSS_CUTTINGS_H
