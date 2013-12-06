#define foreach_ BOOST_FOREACH
#define foreach_r_ BOOST_REVERSE_FOREACH

//using ::in_memory_storages::PkgForSNMP;

namespace tmitter_web_service {

using boost::weak_ptr;
using boost::shared_ptr;
// @TODO: <igor.a.lugansky@gmail.com>
//  состояние нужно сохранять при каждой итерации на случай выкл.
//    так как при включении собъется.
class DataBase {
 public:
    DataBase() { }
    ~DataBase(void) {}

	void ParseCfgSystem(uchar* localCopyBuffer);
	void ParsePkgAndChangeState(uchar* localCopyBuffer, int bufferLength);

private:
	void ParseMainStateTmitter(const uint8* ptrSourceArray);
	void ParseMainParamsExciter(const int number, const uchar* ptrSourceArray);
	void ParseModParams(int number, const uchar* ptrSourceArray);
	void ParseMainParamsPAB(int number, const uchar* ptrSourceArray);
	void ParsePreAmpParams(int number, const uchar* ptrSourceArray);
	void ParseTerminalAmpliferParams(int number, int n,
		const uchar *ptrSourceArray);
	void ParseParamsBCL(int number, const uchar *ptrSourceArray);
	void ParseParamsDB(int number, const uchar* ptrSourceArray);

	//DANGER_ANALOG_NO_FOUND
	void ProcessExciterAnalog(uchar number, const uchar* ptrSourceArray);

public:
  int lengthAllParams___;
#ifdef _DEBUG
  int counterDebug___;
#endif

	std::vector<std::string> stringMsgsQuerySTL;
  // LLevel
  std::vector<int> LLTypeCodesQuerySTL;
  // HLevel
  std::vector<int> HLTypeCodesQuerySTL;
   // МУ или ДУ

  // есть еще Авт. но как реализовать пока не ясно
  std::string typeControl_;

  bool failsReseted_;

  bool printPABLock_[kMaxPABs];
  bool printPABLockEvent_[kMaxPABs];
  bool printPABNoInPower_[kMaxPABs];
  uchar printPABNoInPowerEvent_[kMaxPABs];
  uint printPABUnlock_[kMaxPABs];
  bool printPABInPowerOk_[kMaxPABs];

  int currentQueryIndex_;    // number SNMP events in Queue
};
}
