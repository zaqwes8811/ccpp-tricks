#include "heart/config.h"

// Win troubles
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

#include "kernels.h"

#include "experimental/net/request_mapper.h"
#include "experimental/net/mongoose_handlers.h"
#include "experimental/net/engines.h"
#include "inner_reuse/cc_text_proc.h"
#include "platform_specific/os_access.h"
#include "platform_specific/internationalization.h"

#include <loki/ScopeGuard.h>
#include "hypertable-fix/Common/Logger.h"
#include <boost/chrono/chrono.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>
#include <vector>
#include <queue>

#include <mongoose.h>

#include <errno.h>

using app_abstr::UniqueTextMessage;
using app_abstr::QueueMessageItem;
using std::string;
using snmp::BuildMessageResult;
using std::vector;
using std::queue;
using app_abstr::IpSettingsPair;
using network_engines::NotificationEngine;
using app_abstr::RawStreamSlice;
using text_proc::to_string;
using boost::ref;
using namespace Hypertable;

typedef enum Inner {
  INNER_ALL_RIGHT
} InnerErrCodes;

int exceptionToErrorCode() {
  // http://stackoverflow.com/questions/561997/determining-exception-type-after-the-exception-is-caught
  try {
    throw;
  } catch (dal::RuntimeError& e) {
    return INNER_ALL_RIGHT;
  } catch (Hypertable::Exception& e) {
    try {
      std::stringstream s;
      s << e;
      string str = s.str();
      LOG_INFO(str.c_str());
    } catch (...) {
      LOG_INFO("New exception");
      return INNER_ALL_RIGHT;
    }
    return INNER_ALL_RIGHT;
  } catch (std::invalid_argument& e) {
    try {
      string msg = string("Invalid argument: ") + e.what();
      LOG_INFO(msg.c_str());
    } catch (...) {
      LOG_INFO("New exception");
      return INNER_ALL_RIGHT;
    }
    return INNER_ALL_RIGHT;
  } catch (std::exception& e) {
    LOG_INFO(e.what());
    return INNER_ALL_RIGHT;
  } catch(...) {
    LOG_INFO("Unknown exception.");
    return INNER_ALL_RIGHT;
  }
}

int Kernels::snmpServerIsolate(scopes::AppCloser app
                               , snmp::AgentStore& agent
                               , app_abstr::XCommunity roRwCommunity
                               , int listenerPort)
{
  network_engines::GetGetNextSetEngine engine(listenerPort, roRwCommunity);
  while(true) {
    try {
      int status = engine.iteration(agent);
      if (status == network_engines::GetGetNextSetEngine::GS_ERROR) {
        //boost::this_thread::sleep_for(boost::chrono::seconds(1));
        //LOG_INFO("Error occure: " + string(strerror(errno)));
      }

      if (app.wasInterrupted())
        return KERN_APPLICATION_WAS_TERMINATED;
    } catch (...) {
      int errCode = exceptionToErrorCode();
      if (INNER_ALL_RIGHT != errCode)
        return KERN_UNEXPECTED_FINISHED;
    }
  }
  return KERN_UNEXPECTED_FINISHED;
}

static void reload_awake(const boost::system::error_code& /*e*/
           , boost::asio::deadline_timer* t
           , int step
           , int& r_fsm_timeCheck)
{
  t->expires_at(t->expires_at() + boost::posix_time::seconds(step));
  t->async_wait(boost::bind(reload_awake
                            , boost::asio::placeholders::error
                            , t
                            , step
                            , ref(r_fsm_timeCheck)));
  //LOG_INFO("Tick, world!");
  r_fsm_timeCheck = true;
}

int Kernels::prophylacticRestartIsolate(scopes::AppCloser app
                                 , app_abstr::RebootPack rebootPack
                                 , crosscuttings::ReloaderLock& reloadLock)
{
  boost::asio::io_service io;
  int step = 30;  // sec
  Loki::ScopeGuard _ = Loki::MakeObjGuard(io, &boost::asio::io_service::stop);
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(step));

  int fsm_timeCheck = true;
  t.async_wait(boost::bind(reload_awake
                           , boost::asio::placeholders::error
                           , &t
                           , step
                           , ref(fsm_timeCheck)));

  while (1)
  {
    try {
      io.poll_one();

      if (fsm_timeCheck) {
        if (rebootPack.rebootEnabled) {
          if (reloadLock.itIsDateToReload(rebootPack.dayPeriod)) {
            // check time
            if (rebootPack.m == platform_specific::time_space::getMinute()
                && rebootPack.h == platform_specific::time_space::getHours())
            {
              reloadLock.markDateLastReload();
              platform_specific::os::reboot();
            }
          }
        }
        fsm_timeCheck = false;
      }

      // < 1 minute => catch exactly
      //std::cout << "tick" << std::endl;
      // FIXME: bad
      //boost::this_thread::sleep_for(boost::chrono::seconds(5));
      boost::this_thread::sleep_for(boost::chrono::milliseconds(app_abstr::getKernelLoopTick_ms()));

      if (app.wasInterrupted()) {
        return KERN_APPLICATION_WAS_TERMINATED;
      }
    } catch (...) {
      int errorCode = exceptionToErrorCode();
      if (errorCode != INNER_ALL_RIGHT)
        return KERN_UNEXPECTED_FINISHED;
    }
  }

  return KERN_UNEXPECTED_FINISHED;
}

int FakeKernels::fakeSendNotification(
    scopes::AppCloser app
    , fix_extern_concurent::concurent_bounded_try_queue<app_abstr::QueueMessageItem>& mq
    , crosscuttings::AsyncJournal& agent)
{
  while(true) {
    agent.asyncSendInfo(doUtf8("Проверка кодировки"), app_abstr::SYS_FAILURE_STATE);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

    agent.asyncSendWarning(doUtf8("Проверка кодировки"), app_abstr::SYS_FAILURE_STATE);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

    agent.asyncSendFailure(doUtf8("Проверка кодировки"), app_abstr::SYS_FAILURE_STATE);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

    if (app.wasInterrupted())
      return KERN_APPLICATION_WAS_TERMINATED;

    // http://www.drawbackz.com/stack/392449/how-do-i-get-boostconditiontimed_wait-to-compile.html
    //boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
  }

  return KERN_UNEXPECTED_FINISHED;
}

static void sender_params_awake(const boost::system::error_code& /*e*/
           , boost::asio::deadline_timer* t
           , int step
           , int& r_fsm_timeCheck)
{
  t->expires_at(t->expires_at() + boost::posix_time::seconds(step));
  t->async_wait(boost::bind(sender_params_awake
                            , boost::asio::placeholders::error
                            , t
                            , step
                            , ref(r_fsm_timeCheck)));
  r_fsm_timeCheck = true;
}

int Kernels::paramsSenderIsolate(scopes::AppCloser closer
                                 , snmp::AgentStore& r_agent
                                 , snmp::AgentMessageBuilderPtr builder
                                 , pipeline_store::InMemoryStore_v0_v1_d_a& r_store
                                 , const std::vector<app_abstr::IpSettingsPair> managers
                                 , int sendingIntervals)
{
  using namespace app_abstr;
  using namespace snmp;

  boost::asio::io_service io;
  Loki::ScopeGuard _ = Loki::MakeObjGuard(io, &boost::asio::io_service::stop);
  int step = sendingIntervals;  // sec
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(step));

  int fsm_timeCheck = true;
  t.async_wait(boost::bind(sender_params_awake
                           , boost::asio::placeholders::error
                           , &t
                           , step
                           , ref(fsm_timeCheck)));

  int sPort = 1031;
  HT_CHECK(managers.size() == 1);  // now only one, but prepare to extention
  IpSettingsPair dst = managers.at(0);

  NotificationEngine engineAlive0(sPort, dst);
  NotificationEngine engineParams0(sPort+1, dst);

  // https://events.yandex.ru/lib/talks/2150/
  // DANGER: dark place. Best use async or coroutines. Here finite state mashine (FSM).
  //
  // Must be:
  //   Cancelable
  while (1)
  {
    // DANGER: порядок инструкций важен!
    try {
      io.poll_one();

      if (closer.wasInterrupted())
        return KERN_APPLICATION_WAS_TERMINATED;

      boost::this_thread::sleep_for(boost::chrono::milliseconds(app_abstr::getKernelLoopTick_ms()));

      if (fsm_timeCheck) {
        {
          UniqueParamMessage power = builder->createPowerMsg(
              r_store.getCurrentPower(),
              r_store.getNominalPower(),
              r_store.dnGetSysStatus());

          engineParams0.send(r_agent.buildParamMessage_trapv2(power).second);

          // *100
          UniqueParamMessage twr = builder->createAmplTWRMsg(
                r_store.getAmplTWR()
                , r_store.dnGetSysStatus());

          engineParams0.send(r_agent.buildParamMessage_trapv2(twr).second);

          // termo
          UniqueParamMessage termo = builder->createTemperMsg(
                r_store.getMaxTemperature()
                , r_store.dnGetSysStatus());

          engineParams0.send(r_agent.buildParamMessage_trapv2(termo).second);
        }

        {
          // if not connected Params is does't matter
          const int timeout_ms = 10 * 1000;
          // рально таймаут чтения не 5 ms, а много больше
          const int kCountIterations = timeout_ms / 500;// getKernelLoopTick_ms();
          int it = kCountIterations;
          UniqueAliveMessage a = builder->createAliveMsg(r_store.dnGetSysStatus());
          BuildMessageResult r = r_agent.buildAliveMessage_informs(a);
          engineAlive0.send(r.second);

          while(true)
          {
            io.poll_one();  // non block scheduler
            if (closer.wasInterrupted())
              return KERN_APPLICATION_WAS_TERMINATED;

            // to weak check
            int status = 0;
            RawStreamSlice response = engineAlive0.read(status);
            if (NotificationEngine::READ_SUCCESS == status) {
              r_store.setSnmpMgr0IsOk();
              break;
            }

            if (it < 0) {
              r_store.setSnmpMgr0NotRespond();
              break;
            }
            --it;
          }  // while
        }  // informs space
      }
    } catch (...) {
      int errorCode = exceptionToErrorCode();
      if (errorCode != INNER_ALL_RIGHT)
        return KERN_UNEXPECTED_FINISHED;
    }
  }
  return KERN_UNEXPECTED_FINISHED;
}

static void inc_snmp_timeticket(const boost::system::error_code& /*e*/
           , boost::asio::deadline_timer* t
           , snmp::AgentStore& agent)
{
  t->expires_at(t->expires_at()
                + boost::posix_time::seconds(agent.getTimeTickStep_sec()));
  t->async_wait(boost::bind(inc_snmp_timeticket, boost::asio::placeholders::error, t
                            , boost::ref(agent)));
  agent.incTimeTicks_oneSec();
}

int Kernels::notificationSenderIsolate(
      scopes::AppCloser closer
    , fix_extern_concurent::concurent_bounded_try_queue<app_abstr::QueueMessageItem>& mq
    , snmp::AgentStore& r_agent
    , crosscuttings::SyncJournal& r_journal
    , const std::vector<app_abstr::IpSettingsPair> managers)
{
  using app_abstr::getKernelLoopTick_ms;
  // NOTE: with timers crossplatform troubles
  boost::asio::io_service io;
  Loki::ScopeGuard _ = Loki::MakeObjGuard(io, &boost::asio::io_service::stop);

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(r_agent.getTimeTickStep_sec()));
  t.async_wait(boost::bind(inc_snmp_timeticket, boost::asio::placeholders::error
                           , &t
                           , boost::ref(r_agent)));

  const int sPort = 1030;  //
  const int timeout_ms = 10 * 1000;  // really not worknig so
  HT_CHECK(managers.size() == 1);  // now only one, but prepare to extention
  IpSettingsPair dst = managers.at(0);

  NotificationEngine engine0(sPort, dst);
  const size_t kInformsMaxQueueSize = 1000;//3;
  const int kCountIterations = timeout_ms / 500;//getKernelLoopTick_ms();

  {
    std::queue<QueueMessageItem> fsm_queue;
    bool fsm_readySendNext = true;
    int fsm_countIterations = kCountIterations;
    int32_t currentRequestId = 0;
    while (1) {
     try {
       io.poll_one();

       boost::this_thread::sleep_for(boost::chrono::milliseconds(getKernelLoopTick_ms()));
       if (closer.wasInterrupted())
         return KERN_APPLICATION_WAS_TERMINATED;

       // try first read current
       QueueMessageItem item;
       if (mq.try_pop(item)) {
         HT_CHECK(item.get<0>() == smash::kINFORM_PDU);
         UniqueTextMessage m = item.get<1>();
         crosscuttings::SyncJournal::InRecord r(m.getDateTime(), m.getText());
         r_journal.putRecord(r);
         fsm_queue.push(item);
       }

       if (fsm_queue.size() > kInformsMaxQueueSize) {
         // DANGER: Message can be under sending! Can lost message! Sended message must be in
         //  certen state - sended or time-is-out
         if (fsm_readySendNext) {
           while (fsm_queue.size() > kInformsMaxQueueSize)
             fsm_queue.pop();
         }
       }

       if (fsm_readySendNext) {
         HT_CHECK(fsm_queue.size() <= kInformsMaxQueueSize);
         if (fsm_queue.empty())
           continue;

         QueueMessageItem item = fsm_queue.front();
         BuildMessageResult r = r_agent.buildTextMessage(item);
         engine0.send(r.second);
         currentRequestId = r.first;

         // no-throw
         fsm_readySendNext = false;
         fsm_countIterations = kCountIterations;
       }

       // to weak check
       int status = 0;
       RawStreamSlice response = engine0.read(status);
       if (NotificationEngine::READ_SUCCESS == status) {
         fsm_readySendNext = true;
         fsm_queue.pop();
       } else {
         // DANGER: dark place! no send
         if (fsm_countIterations < 0) {
           fsm_readySendNext = true;
           continue;
         }
         --fsm_countIterations;
         continue;
       }
    } catch (...) {
      int errorCode = exceptionToErrorCode();
      if (errorCode != INNER_ALL_RIGHT)
        return KERN_UNEXPECTED_FINISHED;
    }
  }
  }
  return KERN_UNEXPECTED_FINISHED;
}


int Kernels::httpServerIsolate(scopes::AppCloser app) {
  struct mg_server *pServer = mg_create_server(NULL);
  Loki::ScopeGuard _ = Loki::MakeGuard(mg_destroy_server, &pServer);

  // http://www.linuxjournal.com/article/10680?page=0,2
  //mg_set_option(ctx, "auth_gpass", "./ht");
  mg_set_option(pServer, "listening_port", "8081");
  mg_set_option(pServer, "document_root", http::HttpScope_c::getDocumentRoot().c_str());
  mg_set_option(pServer, "auth_domain", http::HttpScope_c::getDigestAuthDomain().c_str());
  if (errno) {
    LOG_INFO(strerror(errno));
  }

  // FIXME: connect all!
  //mg_set_auth_handler(pServer, &mh_authHandler_digest_md5);
  mg_set_request_handler(pServer, &mhr_useHandler);
  //mg_set_http_error_handler();

  string msg = string("Starting on port %s\n") + mg_get_option(pServer, "listening_port");
  LOG_INFO(msg.c_str());

  for (;;) {
    //int r =
        mg_poll_server(pServer, 1000);

    if (errno) {
      //std::cout << strerror(errno) << std::endl;
    }

    if (app.wasInterrupted()) {
      return KERN_APPLICATION_WAS_TERMINATED;
    }
  }
  return KERN_UNEXPECTED_FINISHED;
}

int Kernels::pipelineEngineIsolate(scopes::AppCloser app
                                   , pipeline_store::InMemoryStore_v0_v1_d_a& r_store
                                   , pipeline_abstr::Actor& r_actor
                                   , int idxActiveEth)
{
  char iteration = 0;
  app_abstr::EthX e = platform_specific::net::get_settings_ethx(idxActiveEth);
  while(true) {
    try {
      if (app.wasInterrupted())
        return KERN_APPLICATION_WAS_TERMINATED;

      // Else commands actions starve!
      boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

      if (iteration % 10 == 0) r_store << r_actor.getConfiguration();
      if (iteration % 90 == 0) r_actor.sendNetworkSettings(e);
      r_store << r_actor.getAllParams();

      ++iteration;
      r_store.setDALConnectionStatusOk();

      if (iteration > 100)
        iteration = 0;
    } catch (...) {
      r_store.setDALConnectionStatusFail();
      int errCode = exceptionToErrorCode();
      if (errCode != KERN_APPLICATION_WAS_TERMINATED)
        continue;
    }
  }
  return KERN_UNEXPECTED_FINISHED;
}

int ExperimentalKernels::storageGuardIsolate()
{
  // https://events.yandex.ru/lib/talks/2308/ Go для С++ разработчиков
  // https://events.yandex.ru/lib/talks/2150/
  // "Yet another threading framework: асинхронная разработка
  // на C++ под мобильные устройства"
  //
  // Troubles:
  //   Нужны не ОС мьютексы и условные переменные
  //
  // Как получить результаты из запросов (с Веба или так)?
  // Async and futures:
  // https://github.com/facebook/folly/tree/master/folly/futures
  //
  // Как обновлять базу данных? Через очередь сообщений
  //
  // https://events.yandex.ru/lib/talks/1760/
  // Введение в асинхронное программирование

  return KERN_UNEXPECTED_FINISHED;
}
