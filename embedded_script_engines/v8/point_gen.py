# coding: utf-8
import re  # регулярные выражения
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
            print(i.replace(';', ' = 0;').replace("  int ", '  this.'))
        else:
            print(i)

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

setPart = """void SetPointY(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->y_ ="""

setPartDown = """ value->Int32Value();
}"""

tempSetPartDown = ""
def printSetPointDown(index, j):
    tempSetPartDown = setPartDown
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) == 0 or index == 0:
            if "bool" in j and '[' not in j and 'vector' not in j:
                tempSetPartDown = tempSetPartDown.replace("Int32Value", "BooleanValue")
        #print(tempSetPartDown)
        return tempSetPartDown
    return "xxxx"

tempSetPart = ""
def printSetPoint(index, j):
    tempSetPart = setPart
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) != 0:
            searchResult = ""
            # тут ищем все вхождения квадратных скобок в имени переменной
            regular = re.compile('\[.*\]')
            searchResult = regular.search( j )
            # удаляем ; и _
            k = j.replace(";", "").replace("_", "")
            # запоминаем индекс внутри квадр скобок и вписываем его в аргументы функции
            if searchResult:
                indexOfArray = searchResult.group()
                indexOfArray = indexOfArray.replace("[","").replace("]","")
                tempSetPart = tempSetPart.replace("& info", "& info, int "+indexOfArray)
            # удаляем символы внутри квадратных скобок вместе со скобками
            if searchResult:
                k = k.replace(searchResult.group(), "")
            # удаляем ;
            j = j.replace(";", "")
            # тут меняем строчную букву на заглавную
            jTemp = k.capitalize()
            k = k.replace(k[0], jTemp[0])
            # главные изменения
            tempSetPart = tempSetPart.replace("void SetPointY", "void set"+k).replace("y_", j)
            #if "SetPointY" not in tempSetPart:
                #print(tempSetPart)
    return tempSetPart

tempGetPoint = ""
def printGetPointUp(index, j):
    tempGetPoint = getPoint
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) != 0: # нечетные для имен полей, четные для типов данных полей
            k = ""
            searchResult = ""
            # тут ищем все вхождения квадратных скобок в имени переменной
            temp = j # переменная для удаления [*]
            regular = re.compile('\[.*\]')
            searchResult = regular.search( j )
            # удаляем ; и _
            k = j.replace(";", "").replace("_", "")

            # запоминаем индекс внутри квадр скобок и вписываем его в аргументы функции
            if searchResult:
                indexOfArray = searchResult.group()
                indexOfArray = indexOfArray.replace("[","").replace("]","")
                tempGetPoint = tempGetPoint.replace("& info", "& info, int "+indexOfArray)

            # удаляем символы внутри квадратных скобок вместе со скобками
            if searchResult:
                k = k.replace(searchResult.group(), "")
            # удаляем ;
            j = j.replace(";", "")
            # тут меняем строчную букву на заглавную
            jTemp = k.capitalize()
            k=k.replace(k[0],jTemp[0])
            # главные изменения

            tempGetPoint = tempGetPoint.replace("void GetPointY", "void get"+k).replace("y_", j)
            return tempGetPoint

def printGetPointDown(index, j):
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) == 0 or index == 0:
            temp = PointDownPart
            if "bool" in j and '[' not in j and 'vector' not in j:
                temp = temp.replace("Integer", "Boolean")
            if "char" in j and "*" not in j and '[' not in j and 'vector' not in j:
                temp = temp.replace("Integer", "Char")
            if "char*" in j:
                temp = temp.replace("Integer", "v8::String")
            if "string" in j and "vector" not in j:
                temp = temp.replace("Integer", "v8::String")
            #if "vector" in j and "string" not in j:
                #temp = temp.replace("Integer", "Array")
            return temp

setPartDownTemp = ""
setPartTemp = ""
up = ""
uptemp = ""
down = ""
downtemp = ""
updn = ""
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
            if "//" in i: # проверка на комментарий правее кода
                for k in i.split("//"):
                    # ниже выделяем имена полей
                    index = 0
                    for jj in k.split(' '):
                        # ниже разбираем по частям, меняем нужные слова, собираем обратно
                        if (index % 2) != 0:
                            setPartTemp = printSetPoint(index, jj).__str__()
                            if "SetPointY" in setPartTemp:
                                setPartTemp = ""
                            uptemp = uptemp + printGetPointUp(index, jj).__str__()
                            # заполнение result
                            if "void" in uptemp and "New" in downtemp:
                                updn = updn + uptemp + downtemp
                            if 'set' in setPartTemp:
                                updn = updn + "\n\n" +setPartTemp
                            # приделываем нижнюю часть set
                            if 'xxxx' not in setPartDownTemp:
                                updn = updn + setPartDownTemp + "\n" + "split"

                            # очистка темпов
                            uptemp = ""
                            downtemp = ""
                            setPartTemp = ""
                            setPartDownTemp = ""
                        else:
                            downtemp = downtemp + printGetPointDown(index,jj).__str__()
                            setPartDownTemp = printSetPointDown(index, jj)
                        index = index + 1
                    break
            else: # здесь тоже выделяем имена полей
                index = 0
                for j in i.split(' '):
                    if (index % 2) != 0:
                        setPartTemp = printSetPoint(index, j).__str__()
                        if "SetPointY" in setPartTemp:
                            setPartTemp = ""

                        uptemp = uptemp + printGetPointUp(index, j).__str__()
                        if "void" in uptemp and "New" in downtemp:
                            updn = updn + uptemp + downtemp
                        if 'set' in setPartTemp:
                            updn = updn + "\n\n" +setPartTemp
                        if 'xxxx' not in setPartDownTemp:
                            updn = updn + setPartDownTemp + "\n" + "split"
                        uptemp = ""
                        downtemp = ""
                        setPartTemp = ""
                        setPartDownTemp = ""
                    else:
                        downtemp = downtemp + printGetPointDown(index,j).__str__()
                        setPartDownTemp = printSetPointDown(index, j)
                    index = index + 1
#print(updn)
result = ""
for i in updn.split("split"):
    if "Boolean::New(value)" in i:
        i = i.replace("int value = ", "bool value = ")
    if "String::New(value)" in i:
        i = i.replace("int value = ", "std::string value = ")
    if "Char::New(value)" in i:
        i = i.replace("int value = ", "char value = ")
    result = result + i
print(result)