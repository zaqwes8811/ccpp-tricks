#ifndef PS_SPACES_H_
#define PS_SPACES_H_

#include "platform_specific/network_main_header.h"

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include <signal.h>

/**
  \brief Very dark place

  \attention use only public method of class! Very important

  \attention How work in windows, with errors in
*/
// http://man7.org/linux/man-pages/man7/signal.7.html
// errno http://man7.org/linux/man-pages/man3/errno.3.html
// errno http://msdn.microsoft.com/en-us/library/5814770t.aspx
namespace scopes {
#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
void sig_term_handler(int signum, siginfo_t *info, void *ptr);
#endif
class AppCloser
    //: public boost::noncopyable
{
public:
  static bool wasInterrupted();// const;
  AppCloser();

private:
  // only copy ctor
  //AppScopeValue(const AppScopeValue&)
  AppCloser& operator=(const AppCloser&);

  //boost::atomic<int> a(0);  // troubles
  //static boost::atomic_bool a;
  static boost::mutex lock_;
  static bool wasInterruption;//(false);

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
  void catch_sigterm();
  friend void sig_term_handler(int signum, siginfo_t *info, void *ptr);
#endif
};

class AppScope
{
public:
  AppScope();
  ~AppScope();
private:
#if defined(_MSC_VER) && ((_MSC_VER == 1500))
  WSADATA wsaData_;
  std::string crtLocale;
#endif
};
}  // space
#endif
