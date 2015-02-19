#ifndef SERVER_SIDE_CODE_CROSSCUTTINGS_OS_ACCESS_H_
#define SERVER_SIDE_CODE_CROSSCUTTINGS_OS_ACCESS_H_

#include "experimental/net/util.h"
#include "heart/cc_g_abstr.h"

#include <vector>
#include <stdexcept>

namespace platform_specific {
namespace os {
/**
  FIXME: Move from here

  for windows "d:\\exe" "exe args"!!
*/
int os_sync_run_command(std::string cmd, std::string params);

int reboot();

int shutdown();
}  // space


namespace time_space {
/**
  Work with time:
    GMT/UTC
    http://stackoverflow.com/questions/1676036/what-should-i-use-to-replace-gettimeofday-on-windows

  \attention NEED VERY good testing!!
*/

/**
 \return "YYYY-MM-DD HH:MM:SS"
*/
std::string appLevelTimeTicket();

/**
  \brief Устанавливает системное время

  \param[in] "2012-04-15 15:15:26"
  // "15.04.2012 15:15:26"
*/
bool appLevelSetSysDateTime(const std::string& time_complect);

int getMinute();
int getHours();
}  // space

namespace net {
app_abstr::EthX get_settings_ethx(int idx);
void set_settings_ethx(const app_abstr::EthX& val, int idx);
}
}  // space

#endif  // SERVER_SIDE_CODE_CROSSCUTTINGS_OS_ACCESS_H_
