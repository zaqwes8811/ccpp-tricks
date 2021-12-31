#ifndef HEART_KERN_H_
#define HEART_KERN_H_

#include "crosscuttings/configurer_adaptor.h"
#include "platform_specific/scopes.h"
#include "experimental/snmp/types.h"
#include "pipeline/pipline_abstr.h"
#include "crosscuttings/local_journal.h"

#include <boost/thread/future.hpp>
#include <async_parallel-fix/data_structures.h>

typedef enum kernels_Codes {
  UNKNOWN_EXCEPTION,
  BOOST_EXCEPTION,
  KERN_APPLICATION_WAS_TERMINATED,
  KERN_UNEXPECTED_FINISHED
} kernels_Codes;

/**
  \brief more like I/O-threads

  name from CUDA "kernels"
*/
class Kernels {
  Kernels() { }
public:
  // typedefs
  typedef boost::packaged_task<int> task_t;

  static int pipelineEngineIsolate(scopes::AppCloser app
                                   , pipeline_store::InMemoryStore_v0_v1_d_a& r_store
                                   , pipeline_abstr::Actor& r_actor
                                   , int idxActiveEth);

  static int httpServerIsolate(scopes::AppCloser app);
  static int snmpServerIsolate(scopes::AppCloser app
                               , snmp::AgentStore& agent
                               , app_abstr::XCommunity roRwCommunity
                               , int listenerPort);

  // FIXME: impl. queue + ...
  static int notificationSenderIsolate(
      scopes::AppCloser app
      , fix_extern_concurent::concurent_bounded_try_queue<app_abstr::QueueMessageItem>&
      , snmp::AgentStore& r_agent
      , crosscuttings::SyncJournal& r_journal
      , const std::vector<app_abstr::IpSettingsPair> managers);

  static int paramsSenderIsolate(scopes::AppCloser app
                                 , snmp::AgentStore& r_agent
                                 , snmp::AgentMessageBuilderPtr builder
                                 , pipeline_store::InMemoryStore_v0_v1_d_a& r_store
                                 , const std::vector<app_abstr::IpSettingsPair> managers
                                 , int sendingIntervals);

  static int prophylacticRestartIsolate(scopes::AppCloser app
                                 , app_abstr::RebootPack rebootPack
                                 , crosscuttings::ReloaderLock& reloadLock);

  // FIXME: alive kernel
};

class FakeKernels {
  FakeKernels() { }
public:
  static int fakeSendNotification(
      scopes::AppCloser app
      , fix_extern_concurent::concurent_bounded_try_queue<app_abstr::QueueMessageItem>&
      , crosscuttings::AsyncJournal& agent);
};

class ExperimentalKernels {
  ExperimentalKernels() { }
public:
  /**
    Now impl InMemStore is incorrect - не потокобезопасна и небезопасна в плане исключений.
    Можно сделать так, что заполнение модели и ее чтение идет в одном потоке используя
    "зеленые" потоки.
  */
  static int storageGuardIsolate();
};

#endif
