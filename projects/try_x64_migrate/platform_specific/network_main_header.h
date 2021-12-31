#ifndef NET_MAIN_HEADER_H_
#define NET_MAIN_HEADER_H_

#include "c_platform_spec_types.h"

#if (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netinet/ip.h>
#  include <arpa/inet.h>

#  define SOCKET_ERROR (-1)
#  define INVALID_SOCKET (-1)
typedef int32_t SockHandle;
typedef struct timeval TimeValue;
// http://linux.die.net/man/2/recvfrom
// http://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined(__MINGW32__)
#    include <winsock.h>

#elif defined(_MSC_VER) && ((_MSC_VER == 1500) || (_MSC_VER >= 1600))
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms740120(v=vs.85).aspx
//#  include <winsock.h>
typedef int32_t SockHandle;
typedef int TimeValue;
#  include <winsock2.h>

#endif

#endif
