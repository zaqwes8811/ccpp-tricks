#ifndef SERIAL_ABSTR_H_
#define SERIAL_ABSTR_H_

#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)) && defined(__linux__)
#  include "intern_linux/__depr_linux_serial_used_asio/linux_serial.h"
#elif defined(_MSC_VER) && ((_MSC_VER == 1500))
#  include "intern_win/serial_channel.h"
#endif

#endif
