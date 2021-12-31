#include "heart/config.h"

#include "platform_specific/scopes.h"
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
#  include "intern_win/wmi.h"
#  include "intern_win/ewf_support.h"
#endif
#include "platform_specific/os_access.h"

#include <hypertable-fix/Common/Logger.h>
#include <hypertable-fix/own_logger.h>

#include <clocale>

namespace scopes {

// On xp not working
// http://stackoverflow.com/questions/15826188/what-most-correct-way-to-set-the-encoding-in-c
void setWinUtf8Out() {

}

AppScope::AppScope()
{
  Hypertable::Logger::initialize("app.log");
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  crtLocale = std::string(setlocale(LC_ALL, NULL));
  // http://www.sql.ru/forum/987239/vs2012-c-vyvod-utf-8-v-konsol-bez-dop-bibliotek
  //setlocale(LC_ALL, ".UTF-8");
  //setlocale(LC_ALL, ".cp1251");
  //setWinUtf8Out();

  /*
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  system("chcp 65001");
  setlocale(LC_ALL, "Russian");
  setlocale(LC_ALL, "ru_RU.UTF-8");
  */

  // http://www.nubaria.com/en/blog/?p=289
  //LOG_INFO(crtLocale + " привет");

  int result = WSAStartup(MAKEWORD(2,2), &wsaData_);
  if (result) {

  }
#ifdef G_FEATURE_USE_WMI_INTERFACE
  HT_CHECK(app_wmi::wmi_create());
#endif
#ifdef FEATURE_EWF
  HT_CHECK(fail_protection::ewf_enable());
#endif
#endif

#ifdef G_DEV_CHECK_DHCP_ON_START
  HT_CHECK(!platform_specific::net::isDHCPOn0());
#endif
}
AppScope::~AppScope()
{
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  setlocale(LC_ALL, crtLocale.c_str());
  WSACleanup();
#ifdef G_FEATURE_USE_WMI_INTERFACE
  app_wmi::wmi_destroy();
#endif
  // Warning: disableEWF not need here!
#endif
}

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
void AppCloser::catch_sigterm()
{
  static struct sigaction _sigact;

  memset(&_sigact, 0, sizeof(_sigact));
  _sigact.sa_sigaction = sig_term_handler;
  _sigact.sa_flags = SA_SIGINFO;

  sigaction(SIGTERM, &_sigact, NULL);
  sigaction(SIGINT, &_sigact, NULL);
  sigaction(SIGQUIT, &_sigact, NULL);

  // Can't catch
  //sigaction(SIGKILL, &_sigact, NULL);
  //sigaction(SIGSTOP, &_sigact, NULL);
}
#endif


bool AppCloser::wasInterrupted() {
  boost::mutex::scoped_lock _(lock_);
  return wasInterruption;

  // http://www.sturmnet.org/blog/2006/07/25/terminating-processes-nicely-on-windows
  // FIXME: for Win false? servers rerun if hard kill
}

AppCloser::AppCloser()
{
  boost::mutex::scoped_lock _(lock_);
  wasInterruption = false;
  // FIXME: how close socket if QtCreator kill application
  //   http://stackoverflow.com/questions/449617/how-should-i-close-a-socket-in-a-signal-handler
  //   http://stackoverflow.com/questions/14010521/cannot-connect-creator-comm-socket-tmp-qt-temp-jh2103-stub-socket-no-such-file
  //
  // http://habrahabr.ru/post/141206/
  // http://stackoverflow.com/questions/14137808/signals-sent-by-qtcreator-on-stop
  // http://stackoverflow.com/questions/449617/how-should-i-close-a-socket-in-a-signal-handler
  // http://http.stackoverflow.com.tool.skopenow.com/questions/16181526/handling-signal-sent-by-stop-while-running-debugger-in-qt-creator
#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
  catch_sigterm();
#endif
}


boost::mutex AppCloser::lock_;
bool AppCloser::wasInterruption = false;

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
void sig_term_handler(int signum, siginfo_t *info, void *ptr)
{
  // DANGER: call from here can nothing!!
  //fprintf(stdout, "SIGTERM received.\n");
    //fflush(stdout);

  // FIXME: make atomic
  // FIXME: can only set some flags - no more!
  boost::mutex::scoped_lock _(AppCloser::lock_);
  AppCloser::wasInterruption = true;
}
#endif
}
