#include "heart/config.h"

#include "internationalization.h"

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__MINGW32__)
#  include <windows.h>
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
#  define __LINUX_HIDE
#elif defined(_MSC_VER) && ((_MSC_VER == 1500) || (_MSC_VER >= 1600))
#  include <windows.h>
#endif

// itoa not standart
//
#include <stdlib.h>
#include <stdio.h>

#if defined(_MSC_VER) && _MSC_VER > 1310
const char * ConvertToUTF8(const wchar_t * pStr) {
    static char szBuf[1024];
    WideCharToMultiByte(CP_UTF8, 0, pStr, -1, szBuf, sizeof(szBuf), NULL, NULL);
    return szBuf;
}
#endif
