# coding: utf-8
__author__ = 'TekScope_Local_Admin'

class_name = """
class Point {
  public:
   Point(int x, int y) : x_(x),
        y_(y) { }
   int x_;
   int y_;
};
"""


for i in class_name.split('\n'):
    if '(' not in i and ":" not in i:
        if len(i) == 0:
            continue
        if i[0] == ' ':
            print i.replace(';', ' = 0;').replace("  int ", '  this.')
        else:
            print i

"""
var Point = function() {


}

var pointInstance = new Point();
"""

class_transmit_code = """
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
	 DataBase() { };
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
  bool printPABNoInPowerEvent_[kMaxPABs];
  bool printPABUnlock_[kMaxPABs];
  bool printPABInPowerOk_[kMaxPABs];


	int currentQueryIndex_;    // number SNMP events in Queue
	"""

getPoint = """
void GetPointY(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->y_;"""

PointDownPart = """  // New api
  // return Integer::New(value);
  info.GetReturnValue().Set(Integer::New(value));
}"""


tempGetPoint = ""


def printGetPointUp(index, j):
    tempGetPoint = getPoint
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) != 0: # нечетные для имен полей, четные для типов данных полей
            k = j.replace(";","").replace("_","")
            j = j.replace(";","")
            jTemp = k.capitalize()
            k=k.replace(k[0],jTemp[0])
            tempGetPoint = tempGetPoint.replace("void GetPointY", "void get"+k).replace("y_", j)
           # print tempGetPoint
            return tempGetPoint

def printGetPointDown(index, j):
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) == 0 or index == 0:
            #print PointDownPart.replace("Integer", "Boolean")
            temp = PointDownPart
            if "bool" in j:
                temp = temp.replace("Integer", "Boolean")
            if "string" in j:
                temp = temp.replace("Integer", "v8::String")
            if "vector" in j:
                temp = temp.replace("Integer", "Array")
            print temp
            return temp


import re  # регулярные выражения
for i in class_transmit_code.split('\n'):
    if '(' not in i and ")" not in i and "{" not in i and "}" not in i \
                            and "#" not in i \
                            and "public:" not in i\
                            and "private" not in i\
                            and "protected" not in i \
                            and "using" not in i:
        p = re.compile("bool""|int""|vector<""|string""|char")
        m = p.search( i )
        if m:
            up = ""
            down = ""
            if "//" in i: # проверка на комментарий правее кода
                for k in i.split("//"):
                    # ниже выделяем имена полей
                    index = 0
                    for jj in k.split(' '):
                        up = printGetPointUp(index, jj).__str__()
                        down = printGetPointDown(index,jj).__str__()
                       # print printGetPointUp(index, jj).__str__() + printGetPointDown(index,jj).__str__()
                        index = index + 1
                    if "New" in down or "void" in up:
                        print  up
                    break
            else: # здесь тоже выделяем имена полей
                index = 0
                for j in i.split(' '):
                    down = printGetPointDown(index, j).__str__()
                    up = printGetPointUp(index, j).__str__()
                   # print printGetPointUp(index, j).__str__() + printGetPointDown(index,j).__str__()
                    index = index + 1
                if "New" in down or "void" in up:
                    print up
                down = ""
                up = ""




