#ifndef OTHER_SETTINGS_H___
#define OTHER_SETTINGS_H___

#include "pipeline/store/store.h"
#include "crosscuttings/configurer_adaptor.h"
#include "experimental/net/util.h"

#include <boost/shared_ptr.hpp>

namespace platform_specific {
class ServiceCoordinator {
public:
  explicit ServiceCoordinator(
      boost::shared_ptr<pipeline_store::InMemoryStore_v0_v1_d_a> db
      , int idxInterface);

  void packNetSettings(std::string &s);

  void packSysSettings(std::string &s
                       , const crosscuttings::ConfigurationGuardian& lock
                       , const crosscuttings::ReloaderLock& r_reloadLock);

  bool applyEthXSettings(const utils::ParametersMap& param
                         , crosscuttings::AsyncJournal& r_j
                         , const pipeline_store::InMemoryStore_v0_v1_d_a& store);

  bool applySysSettings(const utils::ParametersMap& param
                        , crosscuttings::ConfigurationGuardian& r_lock
                        , crosscuttings::AsyncJournal& r_j
                        , const pipeline_store::InMemoryStore_v0_v1_d_a& store);

private:
  // http://stackoverflow.com/questions/5134614/c-const-map-element-access
  std::string at(const utils::ParametersMap& param, const std::string& val);

  const boost::shared_ptr<pipeline_store::InMemoryStore_v0_v1_d_a> m_pStore;
  const size_t m_indexCurrentInterface;

  std::string cSetID;
};
}  // space

#endif
