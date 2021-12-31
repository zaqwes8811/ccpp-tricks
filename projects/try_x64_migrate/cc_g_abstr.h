#ifndef CC_HEADERS_WEB_SERVICE_APP_TYPES_HH_
#define CC_HEADERS_WEB_SERVICE_APP_TYPES_HH_

#include "boost/shared_ptr.hpp"

#include <map>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
//#include <boost/thread/mutex.hpp>

#define foreach_ BOOST_FOREACH
#define foreach_r_ BOOST_REVERSE_FOREACH

namespace app_abstr {
struct IpSettingsPair {
  IpSettingsPair() : ip("127.0.0.1"), port(1) { }
  IpSettingsPair(const std::string& _ip, int _port)
    : ip(_ip), port(_port) {}
  std::string ip;
  unsigned int port;
};

// draw
std::ostream& operator<<(std::ostream& o, const IpSettingsPair& a);

int getKernelLoopTick_ms();

typedef std::vector<unsigned char> RawStreamSlice;

typedef enum mTypes {
  MT_INFO,
  MT_WARNING,
  MT_FAILURE,
  MT_ALIVE,
  MT_PARAM
} mTypes_t;

class sBounds : boost::noncopyable
{
public:
  sBounds() :
    twrHigh(90), twrLow(50)
    , termHigh(90), termLow(0)
    , powerHigh(10), powerLow(10) { }

  /**
    \attention no thread-safe
  */
  bool operator == (const sBounds& rhs) const;

  /**
    \attention no thread-safe
  */
  bool operator != (const sBounds& rhs) const;

  int getTwrHigh() const;
  int getTwrLow() const;
  int getTermHigh() const;
  int getTermLow() const;
  int getPowerHigh() const;
  int getPowerLow() const;

  // set
  void setTwrHigh(int val);
  void setTwrLow(int val);
  void setTermHigh(int val);
  void setTermLow(int val);
  void setPowerHigh(int val);
  void setPowerLow(int val);
  void onHalf();
  void offHalf();

  bool valuePowerIsBad(int value, int nominal_power) const;
  bool valueAmplTWRIsBad(int value) const;
  bool valueTemperIsBad(int value) const;

private:
  /**
    \brief *100
  */
  int twrHigh;
  int twrLow;

  /**
    \brief [W]
  */
  int termHigh;
  int termLow;

  /**
    \brief [value] = % procents from nominal
  */
  int powerHigh;
  int powerLow;

  int rawHigh;
  int rawLow;

  //mutable boost::mutex m_mtx;
};

class UniqueTextMessage
{
 public:
  UniqueTextMessage();
  UniqueTextMessage(std::string _text
                    , int _sysStatus
                    , unsigned int seqNumber);

  std::string getText() const
  { return m_text; }

  std::string getDateTime() const
  { return m_dateTime; }

  // FIXME: hide
  int sysStatus;
  unsigned int sequenceNumber;

private:
  std::string m_text;
  std::string m_dateTime;
};

class UniqueAliveMessage
{
public:
  explicit UniqueAliveMessage(int _sysStatus);

  std::string getDateTime() const
  { return m_dateTime; }

  int m_sysStatus;

private:
  std::string m_dateTime;
};

class UniqueParamMessage
{
public:
  UniqueParamMessage(
      int parId, int value, int sysStatus, int parStatus, int seq);

  const int xmlParamId;

  /**
    \brief Диапазон: -2147483648 ... 2147483647
  */
  const int parValue;

  /**
    FIXME:
    \throw std::invalid_argument
  */
  void checkPavValue_notImpl() const;

  std::string m_dateTime;

  /**
    \attention unique for ever param
  */
  const unsigned int parSeqNumber;  // not this
  const int m_sysStatus;
  int m_parStatus;
};

// waitOrNot, message, type message
typedef boost::tuple<char, UniqueTextMessage, int> QueueMessageItem;

//typedef enum sysSnmpStatuses {
static const int SYS_NORMAL_STATE = 0x00;
static const int SYS_FAILURE_STATE = 0x02;
static const int SYS_WARNING_STATE = 0x01;
//} sysSnmpStatuses_t;

static const int kDalIsConnected = 0x01;
static const int kDalIsNotConnected = 3;

// SNMP status, 0 - stop, 1 - successful, 2 - not receive
static const int kSnmpMgrIsStoped = 0x00;
static const int kSnmpMgrIsOk = 0x01;
static const int kSnmpMgrNotRespond = 0x02;

static const int TP_V0 = 0;
static const int TP_V1 = 1;

// dhcp is on / ip / submask / gateway
typedef boost::tuple<bool, std::string, std::string, std::string> EthX;

// RO, RW
typedef boost::tuple<std::string, std::string> XCommunity;

struct RebootPack {
  RebootPack() :
    m(15)
    , h(12)
    , dayPeriod(1)
    , rebootEnabled(1) { }
  int m;
  int h;
  int dayPeriod;
  int rebootEnabled;

  bool checkSelf() const {
    bool ms = m > 0 && m < 59;
    bool hs = h > 0 && h < 23;
    bool ds = dayPeriod > 0;
    bool rs = rebootEnabled >= 0 && rebootEnabled < 2;
    return (ms && hs && ds && rs);
  }

  bool operator ==(const RebootPack& rhs) {
    return (m == rhs.m) && (h == rhs.h) && (dayPeriod == rhs.dayPeriod)
        && (rebootEnabled == rhs.rebootEnabled);
  }

  bool operator !=(const RebootPack& rhs) {
    return !(operator ==(rhs));
  }
};

static const int PAR_NO = 0;
static const int PAR_NORMAL = 1;
static const int PAR_WARNING = 2;
static const int PAR_ALARM = 3;

typedef enum {
  SMANAG_AVAILABEL,
  SMANAG_NOT_AVAILABEL
} snmpManagerConnectionStatuses;
}

#endif  // CC_HEADERS_WEB_SERVICE_APP_TYPES_H_
