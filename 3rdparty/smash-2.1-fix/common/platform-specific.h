#ifndef PLAT_SPECIFIC_H_
#define PLAT_SPECIFIC_H_



#ifdef HAVE_WINSOCK_H
#include <winsock.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(__MINGW32__)
#    include "production/inner_reuse/strings_win.h"
typedef unsigned int U32;
typedef unsigned int U16;
#  endif
#elif defined(_MSC_VER)
#  if (_MSC_VER == 1500)
typedef unsigned int U32;
typedef unsigned int U16;
#  endif
#else
#  error("Not supported compilater")
#endif


#include <common/config.h>

#endif
