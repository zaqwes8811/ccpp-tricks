#ifndef HELLO_HELLO_
#define HELLO_HELLO_
#define kMaxPABs 10
typedef unsigned char uchar;
typedef unsigned int uint;
class DataBase {
public:
  bool locks_[kMaxPABs];
  bool lock_events_[kMaxPABs];
  bool no_in_powers_[kMaxPABs];
  uchar no_in_power_events_[kMaxPABs];
  uint unlocks_[kMaxPABs];
  bool power_is_ok_[kMaxPABs];
};

#endif  // HELLO_HELLO_
