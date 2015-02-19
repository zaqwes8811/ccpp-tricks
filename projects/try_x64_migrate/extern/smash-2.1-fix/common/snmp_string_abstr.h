#ifndef _snmp_string_h_
#define _snmp_string_h_

/**
  \brief Use in smash snmp library files
*/

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

#ifdef HAVE_CONFIG_H
#  include "agent/_snmp_config.h"
#endif

#ifdef STDC_HEADERS
#  include <string.h>
#  ifndef bcopy
#    define bcopy(a,b,len) memcpy((b),(a),(len))
#  endif
#  ifndef bcmp
#    define bcmp(a,b,len) memcmp((b),(a),(len))
#  endif
#  ifndef bzero
#    define bzero(ptr,len) memset((ptr),0,(len))
#  endif
#elif defined HAVE_STRINGS_H
#  include <strings.h>  // can't compile to windows
#endif

#ifndef strcasecmp
#  define strcasecmp(a,b) snmp_strcasecmp((a),(b))
//extern int snmp_strcasecmp (char *, char *);
extern int snmp_strcasecmp (const char *, const char *);
#endif


#endif /* _snmp_string_h_ */
