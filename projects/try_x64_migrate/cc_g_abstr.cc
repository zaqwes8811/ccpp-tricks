#include "heart/config.h"

#include "heart/cc_g_abstr.h"
#include "platform_specific/os_access.h"
#include "heart/cc_app_constants.h"


namespace app_abstr {

bool sBounds::valuePowerIsBad( int value, int nominal_power ) const {
  boost::mutex::scoped_lock _(m_mtx);
  float fv = (static_cast<float>(nominal_power)/static_cast<float>(100));
  int low = static_cast<int>(floor(fv * (100 - powerLow)));
  int hig = static_cast<int>(floor(fv * (100 + powerHigh)));
  return (value < low) || (value > hig);
}

bool sBounds::valueAmplTWRIsBad( int value ) const {
  boost::mutex::scoped_lock _(m_mtx);
  unsigned char nominal_frw = (FRW_VALUE_H);
  float fv = (static_cast<float>(nominal_frw)/static_cast<float>(100));
  int low = static_cast<int>(floor(fv * (twrLow)));
  int hig = static_cast<int>(floor(fv * (twrHigh)));
  return(value < low) || (value > hig);
}

bool sBounds::valueTemperIsBad(int value) const {
  boost::mutex::scoped_lock _(m_mtx);
  return (value < termLow) || (value > termHigh);
}

bool sBounds::operator == (const sBounds& rhs) const {
  return (twrHigh == rhs.twrHigh)
      && (twrLow == rhs.twrLow)
      && (powerHigh == rhs.powerHigh)
      && (powerLow == rhs.powerLow)
      && (termHigh == rhs.termHigh)
      && (termLow == rhs.termLow);
}

bool sBounds::operator != (const sBounds& rhs) const {
  return !(operator ==(rhs));
}

int sBounds::getTwrHigh() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return twrHigh;
}

int sBounds::getTwrLow() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return twrLow;
}

int sBounds::getTermHigh() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return termHigh;
}

int sBounds::getTermLow() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return termLow;
}

int sBounds::getPowerHigh() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return powerHigh;
}

int sBounds::getPowerLow() const
{
  boost::mutex::scoped_lock _(m_mtx);
  return powerLow;
}

// set
void sBounds::setTwrHigh(int val)
{ boost::mutex::scoped_lock _(m_mtx); twrHigh = val; }

void sBounds::setTwrLow(int val)
{ boost::mutex::scoped_lock _(m_mtx); twrLow = val; }

void sBounds::setTermHigh(int val)
{ boost::mutex::scoped_lock _(m_mtx); termHigh = val; }

void sBounds::setTermLow(int val)
{ boost::mutex::scoped_lock _(m_mtx); termLow = val; }

void sBounds::setPowerHigh(int val)
{ boost::mutex::scoped_lock _(m_mtx); powerHigh = val; rawHigh = val; }

void sBounds::setPowerLow(int val)
{ boost::mutex::scoped_lock _(m_mtx); powerLow = val; rawLow = val; }

void sBounds::onHalf() {
  boost::mutex::scoped_lock _(m_mtx);
  powerHigh /= 2;
  powerLow /= 2;
}

void sBounds::offHalf() {
  boost::mutex::scoped_lock _(m_mtx);
  powerHigh = rawHigh;
  powerLow = rawLow;
}

std::ostream& operator<<(std::ostream& o, const app_abstr::IpSettingsPair& a)
{
  o << a.ip << ":" << a.port << std::endl;
  return o;
}

int getKernelLoopTick_ms() {
  static const int cm_timeout_ms = 5;  // read timeout
  return cm_timeout_ms;
}

UniqueAliveMessage::UniqueAliveMessage(int _sysStatus)
  : m_sysStatus(_sysStatus)
  , m_dateTime(platform_specific::time_space::appLevelTimeTicket())
{

}

UniqueTextMessage::UniqueTextMessage(
    std::string _text, int _sysStatus, unsigned int seqNumber)
  :
  sysStatus(_sysStatus)
  , sequenceNumber(seqNumber)
  , m_text(_text)
  , m_dateTime(platform_specific::time_space::appLevelTimeTicket())
{ }

UniqueTextMessage::UniqueTextMessage()
  :
  sysStatus(0)
  , sequenceNumber(0)
  , m_text("z")
  , m_dateTime("z")
{ }

UniqueParamMessage::UniqueParamMessage(
    int parId, int value, int sysStatus, int parStatus, int seq) :
  xmlParamId(parId),
  parValue(value),
  m_dateTime(platform_specific::time_space::appLevelTimeTicket()),
  parSeqNumber(seq),
  m_sysStatus(sysStatus),
  m_parStatus(parStatus)
{ }
}  // scope
