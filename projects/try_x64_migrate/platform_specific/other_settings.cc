#include "heart/config.h"

#include "platform_specific/other_settings.h"
#include "platform_specific/os_access.h"
#include "inner_reuse/cc_text_proc.h"
#include "inner_reuse/std_own_ext.h"
#include "crosscuttings/async_journal.h"
#include "platform_specific/internationalization.h"

#if defined(_MSC_VER) && ((_MSC_VER == 1500))
#  include "intern_win/wmi.h"
#  include "intern_win/ewf_support.h"
#endif

#include <stdexcept>
#include <iostream>

namespace platform_specific {
using std::string;
using std::map;
using std::cout;
using std::endl;
using utils::ParametersMap;
using utils::wtf_onlyIpv4Mask;
using utils::wtf_onlyIpv4;
using utils::weakCheckIpFormat;
using text_proc::disjoint;
using text_proc::to_string;
using utils::parseQueryStringInternal;
using pipeline_store::InMemoryStore_v0_v1_d_a;
using app_abstr::IpSettingsPair;
using snmp::DomainSettings;
using app_abstr::sBounds;
using text_proc::to_string;
using crosscuttings::ConfigurationGuardian;

bool operator==(const app_abstr::EthX& lhs, const app_abstr::EthX& rhs) {
  return (lhs.get<0>() == rhs.get<0>())
      && (lhs.get<1>() == rhs.get<1>())
      && (lhs.get<2>() == rhs.get<2>())
      && (lhs.get<3>() == rhs.get<3>());
}

bool operator !=(const app_abstr::EthX& lhs, const app_abstr::EthX& rhs) {
  return ! operator ==(lhs, rhs);
}

ServiceCoordinator::ServiceCoordinator(
    boost::shared_ptr<InMemoryStore_v0_v1_d_a> db
    , int idxInterface)
  : m_pStore(db)
  , m_indexCurrentInterface(idxInterface) { }

void ServiceCoordinator::packNetSettings(
    std::string &s
    )
{
  //ParametersMap params;
  s+="&conn="; s+=to_string(m_pStore->dnGetDALConnectionStatus());

  app_abstr::EthX par = net::get_settings_ethx(m_indexCurrentInterface);

  // https://social.msdn.microsoft.com/Forums/en-US/ffc30439-1bb3-4139-bc18-22172152bafb/win32networkadapterconfiguration-ipenabled-behavior-changed-from-xp-to-windows7?forum=windowscompatibility
  s+="&DHCPEnabled=";

  if (par.get<0>()) s+= "1";//params["DHCPEnabled"];
  else s += "0";

  s+="&IPAddress=";          s+= par.get<1>();//params["IPAddress"];
  s+="&IPSubnet=";           s+= par.get<2>();//params["IPSubnet"];
  s+="&DefaultIPGateway=";   s+= par.get<3>();//params["DefaultIPGateway"];
  s+="&IPEnabled=";
  s+="1";//params["IPEnabled"];

  s+="&DNSServerSearchOrder=";
  s+="&WINSPrimaryServer=";
  s+="&WINSSecondaryServer=";
  s+="&GatewayCostMetric=";
}


void ServiceCoordinator::packSysSettings(
    std::string & r_s
    , const crosscuttings::ConfigurationGuardian& lock
    , const crosscuttings::ReloaderLock& r_reloadLock)
{
  IpSettingsPair mgr = lock.getSnmpManagerSettings0();
  IpSettingsPair etv1 = lock.getETV1Settings();
  IpSettingsPair etv2 = lock.getETV2Settings();
  DomainSettings domain = lock.getXmlSettings();
  boost::shared_ptr<sBounds> bounds = lock.getBounds();
  app_abstr::RebootPack rpack = lock.getRebootPack();

  r_s+="&conn=";     r_s += to_string(m_pStore->dnGetDALConnectionStatus());
  r_s+="&TrNum=";    r_s += to_string(m_pStore->getTransmitterAddr());
  r_s+="&ipVtv1=";   r_s += etv1.ip;
  r_s+="&ipVtv2=";   r_s += etv2.ip;
  r_s+="&ipSNMP=";   r_s += mgr.ip;
  r_s+="&portSNMP="; r_s += to_string(mgr.port);
  r_s+="&perdSNMP="; r_s += to_string(lock.getSnmpPeriod0());
  r_s+="&DeviID=";   r_s += to_string(domain.xmlDeviceId);
  r_s+="&DTypID=";   r_s += to_string(domain.xmlParDeviceType);
  r_s+="&portVtv1="; r_s += to_string(etv1.port);
  r_s+="&portVtv2="; r_s += to_string(etv2.port);
  r_s+="&ipExt=";    r_s += lock.getExternIp();
  r_s+="&iFRWLow=";  r_s += to_string(bounds->getTwrLow());
  r_s+="&iFRWMax=";  r_s += to_string(bounds->getTwrHigh());
  r_s+="&iPowLow=";  r_s += to_string(bounds->getPowerLow());
  r_s+="&iPowMax=";  r_s += to_string(bounds->getPowerHigh());
  r_s+="&iTemLow=";  r_s += to_string(bounds->getTermLow());
  r_s+="&iTemMax=";  r_s += to_string(bounds->getTermHigh());
  r_s+="&icd=";      r_s += to_string(m_pStore->getChannelSetup());
  r_s+="&is0=";      r_s += lock.getInf0();
  r_s+="&is1=";      r_s += lock.getInf1();
  r_s+="&rh=";       r_s += to_string(rpack.h);
  r_s+="&rm=";       r_s += to_string(rpack.m);
  r_s+="&rp=";       r_s += to_string(rpack.dayPeriod);
  r_s+="&rb=";
  if (rpack.rebootEnabled) r_s += "1";
  else r_s += "0";
  r_s+="&rl=" + r_reloadLock.getLastReloadTime();

  // type protocol somehow
  r_s += "&type_protocol=" + to_string(lock.getTypeProtocol());

  // snmp listener0
  r_s += "&snmp_listener0_port=" + to_string(lock.getSnmpListener0Port());
  r_s += "&ro_community0=" + lock.getSnmp0ROCommunity();
  r_s += "&rw_community0=" + lock.getSnmp0RWCommunity();

  // version
  r_s += "&app_version=" + string(G_APP_VERSION);
  r_s += "&mib_version=" + to_string(lock.getMibVerion());

  // uid
  r_s += "&uid=" + to_string(lock.getUnuqueId());
}

std::string ServiceCoordinator::at(const utils::ParametersMap& param, const std::string& val) {
  return std_own_ext::at(param, val);
}

bool ServiceCoordinator::applyEthXSettings(const ParametersMap& params
                                           , crosscuttings::AsyncJournal& r_j
                                           , const pipeline_store::InMemoryStore_v0_v1_d_a& store
                                           )
{
  bool dhcpIsEnabled = false;
  if (at(params, "DHCPEnabled") == "1") {
    dhcpIsEnabled = true;
  }
  string newStaticIp = at(params, "IPAddress");
  if (!utils::weakCheckIpFormat(newStaticIp))
    throw std::invalid_argument("Wrong ip addr");

  string newStaticMask = at(params, "IPSubnet");
  if (!utils::weakCheckIpFormat(newStaticMask))
    throw std::invalid_argument("Wrong mask");

  string newGateWay = at(params, "DefaultIPGateway");
  if (!utils::weakCheckIpFormat(newGateWay))
    throw std::invalid_argument("Wrong mask");

  app_abstr::EthX newSet(dhcpIsEnabled, newStaticIp, newStaticMask, newGateWay);
  app_abstr::EthX old = platform_specific::net::get_settings_ethx(m_indexCurrentInterface);
  if (old != newSet) {
    platform_specific::net::set_settings_ethx(newSet, m_indexCurrentInterface);
    r_j.asyncSendWarning(doUtf8("Были сменены настройки сетевого интерфейса eth0.")
                         , store.dnGetSysStatus());
  }

#ifdef FEATURE_EWF
  fail_protection::ewf_commit();
#endif
  return true;
}

bool ServiceCoordinator::applySysSettings(const ParametersMap &params
                                          , crosscuttings::ConfigurationGuardian& r_lock
                                          , crosscuttings::AsyncJournal& r_j
                                          , const pipeline_store::InMemoryStore_v0_v1_d_a& store)
{
  using text_proc::stdStringToInt;

  {
    const int newAddr = stdStringToInt(at(params, "TrNum"));
    if ((newAddr < 0) || (newAddr > 255)) {
      return false;
    }

    if (newAddr != m_pStore->getTransmitterAddr()) {
      r_lock.setTransmitterAddr(newAddr);
    }
  }

  {
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    const IpSettingsPair v = r_lock.getETV1Settings();
    const string ip = at(params, "ipVtv1");
    if (ip != v.ip) {
      // r_j.asyncSendWarning(doUtf8 - WRONG
      r_lock.setETV1Ip(ip);

      // !! after set !! not before
      r_j.asyncSendWarning(doUtf8("Был сменен IP адрес ВТВ1"), store.dnGetSysStatus());
    }

    const unsigned int newPort = stdStringToInt(at(params, "PortVtv1"));
    if (newPort != v.port) {
      r_lock.setETV1Port(newPort);
      r_j.asyncSendWarning(doUtf8("Был сменен порт ВТВ1"), store.dnGetSysStatus());
    }
  }

  {
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    const IpSettingsPair v = r_lock.getETV2Settings();
    const string ip = at(params, "ipVtv2");
    if (ip != v.ip) {
      r_lock.setETV2Ip(ip);
      r_j.asyncSendWarning(doUtf8("Был сменен IP адрес ВТВ2"), store.dnGetSysStatus());
    }

    const unsigned int newPort = stdStringToInt(at(params, "PortVtv2"));
    if (newPort != v.port) {
      r_lock.setETV2Port(newPort);
      r_j.asyncSendWarning(doUtf8("Был сменен порт ВТВ2"), store.dnGetSysStatus());
    }
  }

  {
    const string ip = at(params, "ipExt");
    if (ip != r_lock.getExternIp()) {
      r_lock.setExternIp(ip);
      r_j.asyncSendWarning(doUtf8("Был сменен внешний IP адрес"), store.dnGetSysStatus());
    }
  }

  {
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    const IpSettingsPair mgr = r_lock.getSnmpManagerSettings0();
    const string ip = at(params, "ipSNMP");
    if (ip != mgr.ip) {
      r_lock.setManager0Ip(ip);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP менеджера"), store.dnGetSysStatus());
    }

    unsigned int newPort = stdStringToInt(at(params, "portSNMP"));
    if (newPort != mgr.port) {
      r_lock.setManager0Port(newPort);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP менеджера"), store.dnGetSysStatus());
    }

    int newPeriodSnmp = stdStringToInt(at(params, "perdSNMP"));
    if (newPeriodSnmp != r_lock.getSnmpPeriod0()) {
      r_lock.setSnmpPeriod0(newPeriodSnmp);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP менеджера"), store.dnGetSysStatus());
    }

    snmp::DomainSettings domain = r_lock.getXmlSettings();
    int newDeviceId = stdStringToInt(at(params, "DeviID"));
    int newParDeviceType = stdStringToInt(at(params, "DTypID"));

    snmp::DomainSettings newVal(newDeviceId, newParDeviceType);
    if (!(domain == newVal)) {
      r_lock.setXmlSettings(newVal);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP менеджера"), store.dnGetSysStatus());
    }
  }

  {
    sBounds newBounds;
    newBounds.setTwrLow(stdStringToInt(at(params,"iFRWLow")));
    newBounds.setTwrHigh(stdStringToInt(at(params,"iFRWMax")));
    newBounds.setPowerLow(stdStringToInt(at(params,"iPowLow")));
    newBounds.setPowerHigh(stdStringToInt(at(params,"iPowMax")));
    newBounds.setTermLow(stdStringToInt(at(params,"iTemLow")));
    newBounds.setTermHigh(stdStringToInt(at(params,"iTemMax")));

    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    // usige != is thread safe - vars is local
    if (*(r_lock.getBounds()) != newBounds) {
      r_lock.setBounds(newBounds);
      r_j.asyncSendWarning(doUtf8("Сменены пороги по значениям параметров"), store.dnGetSysStatus());
    }
  }

  // FIXME: not used. what is that?
  //sampler_.iChannelSetup = atoi(p["idc"].c_str());

  {
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    string info0 = at(params, "isi0");
    if (info0 != r_lock.getInf0()) {
      r_lock.setInf0(info0);
      r_j.asyncSendWarning(doUtf8("Сменена служебная информация №0"), store.dnGetSysStatus());
    }

    string info1 = at(params, "isi1");
    if (info1 != r_lock.getInf1()) {
      r_lock.setInf1(info1);
      r_j.asyncSendWarning(doUtf8("Сменена служебная информация №1"), store.dnGetSysStatus());
    }
  }

  {
    app_abstr::RebootPack newRPack;
    newRPack.h = stdStringToInt(at(params, "rh"));
    newRPack.m = stdStringToInt(at(params, "rm"));
    newRPack.dayPeriod = stdStringToInt(at(params, "rp"));
    newRPack.rebootEnabled = stdStringToInt(at(params, "rb"));
    if (!newRPack.checkSelf())
      throw std::invalid_argument("Wrong reboot params");

    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    app_abstr::RebootPack oldRPack = r_lock.getRebootPack();
    if (oldRPack != newRPack) {
      r_lock.setRebootPack(newRPack);
      r_j.asyncSendWarning(doUtf8("Сменена служебная информация №1"), store.dnGetSysStatus());
    }
  }

  // FIXME: type protocol checkbox
  {
    int typeProtocol = stdStringToInt(at(params, "type_protocol"));
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    int old = r_lock.getTypeProtocol();
    if (old != typeProtocol) {
      r_lock.setTypeProtocol(typeProtocol);
      r_j.asyncSendWarning(doUtf8("Сменен тип протокола"), store.dnGetSysStatus());
    }
  }

  // FIXME: snmp GET/GETNEXT/SET port and RO and RW community
  {
    int port = stdStringToInt(at(params, "snmp_listener0_port"));
    string ro = at(params, "ro_community0");
    string rw = at(params, "rw_community0");

    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    if (port != r_lock.getSnmpListener0Port()) {
      r_lock.setSnmpListener0Port(port);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP агента"), store.dnGetSysStatus());
    }

    if (ro != r_lock.getSnmp0ROCommunity()) {
      r_lock.setSnmp0ROCommunity(ro);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP агента"), store.dnGetSysStatus());
    }

    if (rw != r_lock.getSnmp0RWCommunity()) {
      r_lock.setSnmp0RWCommunity(rw);
      r_j.asyncSendWarning(doUtf8("Сменены настройки SNMP агента"), store.dnGetSysStatus());
    }
  }

  {
    const int uid = stdStringToInt(at(params, "uid"));
    boost::lock_guard<ConfigurationGuardian> _(r_lock);
    if (uid != r_lock.getUnuqueId()) {
      r_lock.setUniqueId(uid);
      r_j.asyncSendWarning(doUtf8("Был сменен UID передатчика"), store.dnGetSysStatus());
    }
  }

  return true;
}
}  // space
