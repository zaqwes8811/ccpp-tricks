#ifndef COMPONENTS_RTOS_TYPES_APP_REUSE_TYPES_H_
#define COMPONENTS_RTOS_TYPES_APP_REUSE_TYPES_H_
/**
  \attention int have diff size  but > 16 => int32 -> long
  http://msdn.microsoft.com/en-us/library/s3f49ktz.aspx
  http://en.wikipedia.org/wiki/Integer_(computer_science)
  http://stackoverflow.com/questions/94591/what-is-the-maximum-value-for-a-int32

  http://stackoverflow.com/questions/271076/what-is-the-difference-between-an-int-and-a-long-in-c

  http://stackoverflow.com/questions/4329777/is-long-guaranteed-to-be-at-least-32-bits

  Dep on machine and compilar

  x64 http://www.viva64.com/en/a/0004/
*/

/**
  \attention Danger: Change тип очень опасно!! —то раз подумать и все проверить
  uchar -> char - искажает почти все показани¤ !
*/

// FIXME: Use boost::uintXX_t and other?
// FIXME: x86?
#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
#  include <stdint.h>   // C99
typedef unsigned long uint32_lo_t;
#  define INLINE inline
#elif defined(__clang__) && defined(__linux__)
#  define INLINE inline
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined (__MINGW32__)
#  define INLINE __inline
typedef unsigned long uint32_lo_t;  // just int is wrong!!
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
#elif defined(_MSC_VER) && ((_MSC_VER == 1500) || (_MSC_VER >= 1600))
typedef unsigned long uint32_lo_t;  // just int is wrong!!
typedef long int32_lo_t;  // long
// in V8 int32_t - just int
typedef unsigned int uint32_t;  // just int is wrong!!
typedef int int32_t;  // long

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned char slot_t;
typedef uint16_t doubled_slot_t ;

// https://social.msdn.microsoft.com/Forums/vstudio/en-US/7d0dd512-b32c-46ea-82c8-f629df27a94b/error-c2054-expected-to-follow-inline?forum=vclanguage
#  define INLINE __inline
#endif

#define G_INT32_VAL_BYTESIZE (4)

static INLINE unsigned long getMaxUInt32() { return 0xFFFFFFFF-1; }

#endif  // COMPONENTS_RTOS_TYPES_APP_REUSE_TYPES_H_
