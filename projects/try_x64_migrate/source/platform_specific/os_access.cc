#include "heart/config.h"

#include "inner_reuse/cc_text_proc.h"
#include "platform_specific/os_access.h"

#if defined(_MSC_VER) && ((_MSC_VER == 1500))
#  include "intern_win/os.h"
#  ifdef G_FEATURE_USE_WMI_INTERFACE
#    include "intern_win/wmi.h"
#  endif
#elif (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
#  include "intern_linux/os.h"
#endif

#include <hypertable-fix/own_logger.h>

#include <algorithm>
#include <string>

namespace platform_specific {
using std::string;
using std::vector;
using std::reverse;
using text_proc::to_string;
using text_proc::IntToUChar;
using text_proc::IntToChar;
using text_proc::int2var_weigth_str;

namespace time_space {
int getMinute()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  return ltm->tm_min;
}

int getHours()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  return ltm->tm_hour;
}

vector<char> getSysTime_char() {
  vector<char> trank_r;
  time_t now = time(0);
  tm *ltm = localtime(&now);
  IntToChar(trank_r, (1900 + ltm->tm_year), 4);
  trank_r.push_back('-');
  IntToChar(trank_r, 1 + ltm->tm_mon, 2);
  trank_r.push_back('-');
  IntToChar(trank_r, ltm->tm_mday, 2);
  trank_r.push_back(' ');
  IntToChar(trank_r, ltm->tm_hour, 2);
  trank_r.push_back(':');
  IntToChar(trank_r, ltm->tm_min, 2);
  trank_r.push_back(':');
  IntToChar(trank_r, ltm->tm_sec, 2);
  return trank_r;
}

/**
 \return "YYYY-MM-DD HH:MM:SS"
*/
std::string getSysDateTime() {
  vector<char> ticket = getSysTime_char();
  return string(ticket.begin(), ticket.end());
}

std::string GetSysTime(int& err) {
  return getSysDateTime();
}

std::string appLevelTimeTicket()
{ return getSysDateTime(); }

bool appLevelSetSysDateTime(const std::string& time_complect) {
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  return intern_win::time_space::set_sys_date_time(time_complect);
#elif (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
  return intern_linux::time_space::set_sys_date_time(time_complect);
#endif
}
}  // space

namespace os {
int os_sync_run_command(std::string cmd, std::string params) {
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  return intern_win::os::os_sync_run_command(cmd, params);
#else
  return intern_linux::os::os_run_command(cmd, params);
#endif
}

int reboot() {
#if (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
  return intern_linux::os::reboot();
#elif defined(_MSC_VER) && ((_MSC_VER == 1500))
  return intern_win::os::os_reboot();
#endif
}

int shutdown() {
#if (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
  return intern_linux::os::shutdown();
#elif defined(_MSC_VER) && ((_MSC_VER == 1500))
  return true;
#endif
}
}  // space

namespace net {
app_abstr::EthX get_settings_ethx(int idx) {
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  return intern_win::net::dvr_getSettingsEthX(idx);
#elif (defined(__GNUC__) || defined(__GNUG__) || (__clang__)) && defined(__linux__)
  string filename = intern_linux::net::getInterfaceFileName();
  return intern_linux::net::dvr_get_ethx(idx, filename);
#endif
}

void set_settings_ethx(const app_abstr::EthX& val, int idx)
{
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  return intern_win::net::dvr_setSettingsEthX(val, idx);
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
  string filename = intern_linux::net::getInterfaceFileName();
  return intern_linux::net::dvr_set_ethx(val, idx, filename);
#endif
}
}  // space
}  // space
