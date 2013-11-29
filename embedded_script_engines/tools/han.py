# coding: utf-8
import re  # регулярные выражения

__author__ = 'TekScope_Local_Admin'

# ПЕЧАТАТЬ ЛИ МАССИВЫ?????
# 0 - нет
# 1 - да
check_array_print = 0

print("\n")
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
  uchar printPABNoInPowerEvent_[kMaxPABs];
  uint printPABUnlock_[kMaxPABs];
  bool printPABInPowerOk_[kMaxPABs];


	int currentQueryIndex_;    // number SNMP events in Queue
	"""


def removeComments(transmittingCode):
    deletingString = ""
    regular = re.compile('\/\/.*')
    searchResult = regular.search(transmittingCode)
    if searchResult:
        deletingString = searchResult.group()
        #print searchResult.group()
    return transmittingCode.replace(deletingString, "")

#print removeComments(class_transmit_code)

def deleteDoubleSpaces(transmittedString):
    return transmittedString.replace("  ", " ")

# возвращает строку, в которой содержится все пары тип + имя переменной
def extract_var_declaration(class_transmit_code_):
    result = ""
    for i in class_transmit_code_.split('\n'):
        if '(' not in i and ")" not in i and "{" not in i and "}" not in i \
            and "#" not in i \
            and "public:" not in i \
            and "private" not in i \
            and "protected" not in i \
            and "using" not in i:
            p = re.compile("bool""|int""|vector<""|string""|char")
            m = p.search(i)
            if m:
                i = removeComments(i)
                i = deleteDoubleSpaces(i)
                result = result + i + '\n'
    return getTypeAndVarList(result)


def PreparingToGetTypeAndVarList(transmittingString):
    transmittingString = transmittingString.replace('\t', " ") \
        .replace(';', "") \
        .replace('\n\t', " ") \
        .replace("  ", " ") \
        .replace('\n', " ")
    transmittingString = transmittingString.replace("  ", " ")
    return transmittingString


def getTypeAndVarList(typeAndVarStrings):
    tempString = ""
    result = []
    type = ""
    name = ""
    index = 0
    tempString = PreparingToGetTypeAndVarList(typeAndVarStrings)
    for splitted_string in tempString.split(' '):
        if splitted_string != "":
            if index % 2 != 0:
                type = splitted_string
                if (name != "") and type != "":
                    result.append((type, name))
            else:
                name = splitted_string
        index = index + 1
    return result


def transmitCTypeToV8(type, typeFunc):
    result = ""
    if typeFunc == "get":
        if type == "int" or type == "uint"\
                         or type == "char" \
                         or type == "uchar":
            result = "Integer"
    if typeFunc == "set":
        if type == "int" or type == "uint" \
                         or type == "uchar" \
                         or type == "char":
            result = "Int32"
    if type == "bool":
        result = "Boolean"
    #bad
    #if type == "string" or type == "std::string":
        #result == "v8::String"
    if "string" in type:
        result = "v8::String"
    return result

def transmitSignedUnsignedTypes(type):
    if type == "uchar":
        return "unsigned char"
    if type == "uint":
        return "unsigned int"
    return type

def getFuncName(name):
    nameCapitalized = name.capitalize()
    return name.replace("_", "").replace(name[0], nameCapitalized[0]);


def make_scalar_getter(type, name):
    result = \
"\n" + "static void v8_get_" + getFuncName(name) + """(Local<String> name,
    const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  """ + transmitSignedUnsignedTypes(type) + " value = static_cast<Point*>(ptr)->" + name + ''';
  info.GetReturnValue().Set(''' + transmitCTypeToV8(type, "get") + """::New(value));
}
"""
    return ArrayOrNotArray(result, name, type, "get")


def make_scalar_setter(type, name):
    result = \
"\n" + "static void v8_set_" + getFuncName(name) + '''(Local<String> property, Local<Value> value,
    const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<''' + "DataBase" + "*>(ptr)->" + name + "= value->" + transmitCTypeToV8(type, "set") \
  + "Value();" + '''
}
'''
    return ArrayOrNotArray(result, name, type, "set")

def make_getter_and_setter_add(type, name):
    result = "  result->SetAccessor(String::New(\"" + name +"\"), v8_get_" + name + ", v8_set_" + name + ");"

    result = ArrayOrNotArray(result, name, type, "add")

    return result

def ArrayOrNotArray(result, name, type, typeFunc):
    if check_array_print == 0:
        if "[" not in name and "vector" not in type:
            return result
        else:
            return ""
    if check_array_print == 1:
        return result
    if typeFunc == "add":
        return "error: bad logic (in make_getter_and_setter_add) or " + check_array_print + " != 0 or 1, default = 0"
    if typeFunc == "set":
        return "error: bad logic (in make_scalar_setter) or " + check_array_print + " != 0 or 1, default = 0"
    if typeFunc == "get":
        return "error: bad logic (in make_scalar_getter) or " + check_array_print + " != 0 or 1, default = 0"


# ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
# еще добавил формирование функции CreateBlueprint
def makeAll(type_and_var_list):
   result = """v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate) {
"""
   for elem in type_and_var_list:
      result = result + make_getter_and_setter_add(*elem) + "\n"

   result = result + """
}"""
   result = result.replace('\n\n', '\n')
   for elem in type_and_var_list:
       result = result + make_scalar_getter(*elem) + make_scalar_setter(*elem)

   result = result.replace('\n ', '\n')
   result = result.replace('\n\n','\n').replace('\n\n}','\n}')
   result = result.replace("}\n", "}\n\n")
   return result

# 0 - вывод без массивов!
# 1 - вывод с массивами (по умолчанию 0)
check_array_print = 0

if __name__ == '__main__':
    type_and_var_list = extract_var_declaration(class_transmit_code)
    # такой будет вывод, когда подключим все массивы и функции
    if False:
        for elem in type_and_var_list:
            print(make_getter_and_setter_add(*elem))

        for elem in type_and_var_list:
            print(make_scalar_getter(*elem))
            print(make_scalar_setter(*elem))
    else:
    # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
        print(makeAll(type_and_var_list))



