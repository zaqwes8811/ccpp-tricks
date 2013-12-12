#ifndef HELLO_HELLO_
#define HELLO_HELLO_
#define kMaxPABs 10
typedef unsigned char uchar;
typedef unsigned int uint;
class DataBase {
public:
  bool printPABLock_[kMaxPABs];
  bool printPABLockEvent_[kMaxPABs];
  bool printPABNoInPower_[kMaxPABs];
  uchar printPABNoInPowerEvent_[kMaxPABs];
  uint printPABUnlock_[kMaxPABs];
  bool printPABInPowerOk_[kMaxPABs];
};

#endif  // HELLO_HELLO_
