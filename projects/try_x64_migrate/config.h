#ifndef CC_HEADERS_WEB_SERVICE_APP_CFG_H_
#define CC_HEADERS_WEB_SERVICE_APP_CFG_H_

//#define BOOST_THREAD_USES_ATOMIC
#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_CHRONO_HEADER_ONLY

#include <boost/detail/endian.hpp>

#define G_APP_VERSION ("4.0.0")

// http://stackoverflow.com/questions/2324658/how-to-determine-the-version-of-the-c-standard-used-by-the-compiler
#if defined(__cplusplus)
/**
  Очень хотелось бы использовать C++11, но будут проблемы с кросскомпиляцией.
  Now - январь 2015
*/
#  if (__cplusplus > 199711L)
#    error("C++ standart version <= C++98");
#  endif
#endif

// x64 not supported!
// http://blogs.msdn.com/b/oldnewthing/archive/2006/09/06/742710.aspx
// http://www.viva64.com/en/a/0004/
// http://stackoverflow.com/questions/163058/how-can-i-detect-if-im-compiling-for-a-64bits-architecture-in-c
#if defined(_WIN64) || defined(WIN64) || defined(_M_X64) || defined(__amd64__)
#  error("This project not design for support x64. x86-only")
#endif

// http://stackoverflow.com/questions/3826832/is-there-a-portable-way-to-print-a-message-from-the-c-preprocessor
#if defined(BOOST_LITTLE_ENDIAN)
//#pragma message("Little endian")
//#warning "Little endian"
#elif defined(BOOST_BIG_ENDIAN)
#  error "Big endian not tested. I don't know must be issues or not. May be in SNMP mib handlers"
#else
#  error "unable to determine system endianness"
#endif

// Oses
// http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)) && defined(__linux__)
//#  define G_UBUNTU_12_04_DESK
#  define G_DEBIAN_SK_MAT91SAM9G45_M10
#elif defined(_MSC_VER) && ((_MSC_VER == 1500))
#  define WINVER 0x0501 // xp
//#  define G_WINDOWS_DESK
#  define G_WINDOWS_EMB
#endif

// http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)) && defined(__linux__)

#elif defined(_MSC_VER) && ((_MSC_VER == 1500))
// WinXp/Win7/vs2008ee  - not vs2008pro
// http://stackoverflow.com/questions/70013/how-to-detect-if-im-compiling-code-with-visual-studio-2008
#  define NOMINMAX
// http://stackoverflow.com/questions/2281970/cross-platform-defining-define-for-macros-function-and-func
#  define __func__ __FUNCTION__
#  define G_PURGE_SRC_HANDLERS
#  define G_FEATURE_USE_WMI_INTERFACE
#  if defined(G_WINDOWS_EMB)
#    define FEATURE_EWF
#  endif

#elif (defined(__GNUC__) || defined(__GNUG__)) && defined (__MINGW32__)
#  define G_WINDOWS_OS
#  error("MINGW troubles with comsupp(w).lib")

#elif defined(_MSC_VER) && ((_MSC_VER >= 1600))
/**
  Очень хотелось бы, но версия VS 2010 и выше реализует часть нового стандарта.
  Для профессиональной версии скорее всего все ок, а вот экспресс похоже имеет
  необходимые макросы, но не имеет реализаций, и это сбивает Boost.

  Версия Express есть для VS 2012, но возможно ее нет для VS2013 по крайней мере пока.
*/
#  error("If used VS2010 Express, code not compiled. Troubles with C++11 features and Boost")
// http://stackoverflow.com/questions/3499487/replacing-native-vs-2010-vc10-tr1-libraries-with-boost-tr1
#  define _HAS_CPP0X=0
//#  define BOOST_NO_CXX11_SMART_PTR
//#  define BOOST_NO_CXX11_RVALUE_REFERENCES

#else
#  error("Unknow compiler. Not worked with it")
#endif

/**
  \brief No effect on develop os system
  - can't change network settings - only print message
  - can't reboot or shutdown - only ...
  - can't use ewf fow WinEmb
  - can't change system time
*/
//#define G_DEV_OS_PROTECTION
//#define G_DEV_CHECK_DHCP_ON_START
#define G_DEV_CHECK_ONLY_ONE_NET_ETH
//#define G_DEV_USE_MODEL

//#define FEATURE_CHECK_CONNECTIONS
#define FEATURE_AAT_SNMP
#define G_FEATURE_SEND_IP_SOME_OPTION
#define FEATURE_SEND_ALL_CHANNELS
#define GPATCH_DISABLE_ANALOG
#define GPATCH_HIDE_AND_REPLACE_MSGS
//#define GPATCH_DONT_SHOW_NOSYNC
//#define GPATH_HIDE_HYPERTABLE_SPECIFIC
//#define G_MAP_NEVA2RTS
#define G_MAP_MART2AAT
#define FEATURE_AAT_CONFIGURATION

#ifdef POWER_PAC_OS_PLATFORM
#  define FEATURE_CHECK_SERIAL_RESPONSE  // Feature?
#  define GFEATURE_ENABLE_WATCHDOG  // Только с PowerPack, not Linux
#  define FEATURE_FULL_DISCONNECT  // Не помню что значит
// About:
//   Run with СДК-5
#  define FEATURE_SNMP_INTERMEDIARIES_MANAGER  // Если и другая конфигурация
//#define GFEATURE_HIGH_POWER  // Исходно в маломощных не подключены все блоки

//#define PATH_USE_ONLY_TCPIP
//#define PATH_DISCONNECT_SERIAL0_TASK  // Подключает фейковый обработчик пакетов
#  define GPATCH_DISCONNECT_ANALOG
#  define DANGER_ANALOG_NO_USED
#  define GPATCH_DISCONNECT_FOR_WIN
#  define GPATCH_HIDE_REPORTS_FORMER
#  define GPATCH_ADAPT_ANDROID_RTC
#  define GPATCH_USER_LOGIN_IS_CONST
#  define G_TO_REPLACE_DOUBLE_CONV
#  define GPATCH_TWR_FROM_PAB

//@Thresholds
#  define G_MAX_LOG_RECORDS  2000
#  define G_LOG_SHIFT_SIZE  1
#  define G_TIME_MODE 0 // 0 - 24
// iss8 - проблема при работе с *.css файлами, проявляется пока
// только в Chrome
//#define TRY_FIX_CSS_BUG  // no work
//#define DISCONNECT_FTP_TASK

// Максимально число одновременно работающих пользователей
#  define GWS_MAX_CONNECTIONS  10
#  define GWS_STACK_SIZE_CLIENT_HANDLER     4096*4
#  ifdef GFEATURE_ENABLE_WATCHDOG
#    define G_TIMEWAIT_WATCHDOG 5000  // ms.
#  endif
#  define GWDT_NUTOS_ADAPT
#endif

#endif  // CC_HEADERS_WEB_SERVICE_APP_CFG_H_
