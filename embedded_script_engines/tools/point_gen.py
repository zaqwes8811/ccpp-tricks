# coding: utf-8
import re  # регулярные выражения

# Third_party
from generator.cpp import utils
from generator.cpp import tokenize
from generator.cpp import ast


def regenerate_point_class(class_name):
    """
    var Point = function() { }

    var pointInstance = new Point();
    """
    for i in class_name.split('\n'):
        if '(' not in i and ":" not in i:
            if len(i) == 0:
                continue
            if i[0] == ' ':
                print(i.replace(';', ' = 0;').replace("  int ", '  this.'))
            else:
                print(i)


class Field(object):
    pass


def make_scalar_getter_template(field_type, field_name, class_name):
    """
    About:
    class Point {
        public:  // bad, but now be it
        int x;
    };

    """
    v8_recoder = {'int': 'Integer'}
    if field_name not in v8_recoder:
        return None

    template = """
        void v8_getter_""" + field_name + """(Local<String> name,
                       const PropertyCallbackInfo<Value>& info) {
          Local<Object> self = info.Holder();
          Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
          void* ptr = wrap->Value();
          """ + field_type + """ value = static_cast<"""+class_name+"""*>(ptr)->y_;
          info.GetReturnValue().Set(""" + v8_recoder[field_type] + """::New(value));
        }"""

    return template


GETTER_TEMPLATE_ = """
void GetPointY(Local<String> name,
               const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  int value = static_cast<Point*>(ptr)->y_;"""

POINT_DOWN_PART_ = """
  info.GetReturnValue().Set(Integer::New(value));
}"""

SETTER_PART_ = """void SetPointY(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<Point*>(ptr)->y_ ="""

SETTER_PART_DOWN_ = """ value->Int32Value();
}"""


def printSetPointDown(index, j):
    tempSetPartDown = SETTER_PART_DOWN_
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) == 0 or index == 0:
            if "bool" in j and '[' not in j and 'vector' not in j:
                tempSetPartDown = tempSetPartDown.replace("Int32Value", "BooleanValue")
                #print(tempSetPartDown)
        return tempSetPartDown
    return "xxxx"


def print_set_point(index, in_string):
    setter_part_tmp = SETTER_PART_
    in_string = in_string.replace(" ", "")
    if len(in_string) != 0:
        if (index % 2) != 0:
            # тут ищем все вхождения квадратных скобок в имени переменной
            regular = re.compile('\[.*\]')
            search_result = regular.search(in_string)
            # удаляем ; и _
            k = in_string.replace(";", "").replace("_", "")
            # запоминаем индекс внутри квадр скобок и вписываем его в аргументы функции
            if search_result:
                index_of_array = search_result.group()
                index_of_array = index_of_array.replace("[", "").replace("]", "")
                setter_part_tmp = setter_part_tmp.replace("& info", "& info, int " + index_of_array)
                # удаляем символы внутри квадратных скобок вместе со скобками
            if search_result:
                k = k.replace(search_result.group(), "")
                # удаляем ;
            in_string = in_string.replace(";", "")
            # тут меняем строчную букву на заглавную
            jTemp = k.capitalize()
            k = k.replace(k[0], jTemp[0])
            # главные изменения
            setter_part_tmp = \
                setter_part_tmp \
                    .replace("void SetPointY", "void set" + k) \
                    .replace("y_", in_string)
    return setter_part_tmp


def printGetPointUp(index, j):
    tempGetPoint = GETTER_TEMPLATE_
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) != 0: # нечетные для имен полей, четные для типов данных полей
            k = ""
            searchResult = ""
            # тут ищем все вхождения квадратных скобок в имени переменной
            temp = j # переменная для удаления [*]
            regular = re.compile('\[.*\]')
            searchResult = regular.search(j)
            # удаляем ; и _
            k = j.replace(";", "").replace("_", "")

            # запоминаем индекс внутри квадр скобок и вписываем его в аргументы функции
            if searchResult:
                indexOfArray = searchResult.group()
                indexOfArray = indexOfArray.replace("[", "").replace("]", "")
                tempGetPoint = tempGetPoint.replace("& info", "& info, int " + indexOfArray)

            # удаляем символы внутри квадратных скобок вместе со скобками
            if searchResult:
                k = k.replace(searchResult.group(), "")
                # удаляем ;
            j = j.replace(";", "")
            # тут меняем строчную букву на заглавную
            jTemp = k.capitalize()
            k = k.replace(k[0], jTemp[0])
            # главные изменения
            tempGetPoint = tempGetPoint.replace("void GetPointY", "void get" + k).replace("y_", j)
            return tempGetPoint


def printGetPointDown(index, j):
    j = j.replace(" ", "")
    if len(j) != 0:
        if (index % 2) == 0 or index == 0:
            temp = POINT_DOWN_PART_
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


def make(source):
    setPartDownTemp = ""
    uptemp = ""
    down_temp = ""
    up_down = ""
    for i in source.split('\n'):
        if '(' not in i and ")" not in i and "{" not in i and "}" not in i \
            and "#" not in i \
            and "public:" not in i \
            and "private" not in i \
            and "protected" not in i \
            and "using" not in i:
            p = re.compile("bool""|int""|vector<""|string""|char")
            m = p.search(i)
            if m:
                if "//" in i: # проверка на комментарий правее кода
                    for k in i.split("//"):
                        # ниже выделяем имена полей
                        index = 0
                        for jj in k.split(' '):
                            # ниже разбираем по частям, меняем нужные слова, собираем обратно
                            if (index % 2) != 0:
                                setPartTemp = print_set_point(index, jj).__str__()
                                if "SetPointY" in setPartTemp:
                                    setPartTemp = ""
                                uptemp = uptemp + printGetPointUp(index, jj).__str__()
                                # заполнение result
                                if "void" in uptemp and "New" in down_temp:
                                    up_down = up_down + uptemp + down_temp
                                if 'set' in setPartTemp:
                                    up_down = up_down + "\n\n" + setPartTemp
                                    # приделываем нижнюю часть set
                                if 'xxxx' not in setPartDownTemp:
                                    up_down = up_down + setPartDownTemp + "\n"
                                    # очистка темпов
                                uptemp = ""
                                down_temp = ""
                                setPartDownTemp = ""
                            else:
                                down_temp = down_temp + printGetPointDown(index, jj).__str__()
                                setPartDownTemp = printSetPointDown(index, jj)
                            index = index + 1
                        break
                else: # здесь тоже выделяем имена полей
                    index = 0
                    for j in i.split(' '):
                        if (index % 2) != 0:
                            setPartTemp = print_set_point(index, j).__str__()
                            if "SetPointY" in setPartTemp:
                                setPartTemp = ""

                            uptemp = uptemp + printGetPointUp(index, j).__str__()
                            if "void" in uptemp and "New" in down_temp:
                                up_down = up_down + uptemp + down_temp
                            if 'set' in setPartTemp:
                                up_down = up_down + "\n\n" + setPartTemp
                            if 'xxxx' not in setPartDownTemp:
                                up_down = up_down + setPartDownTemp + "\n"
                            uptemp = ""
                            down_temp = ""
                            setPartTemp = ""
                            setPartDownTemp = ""
                        else:
                            down_temp = down_temp + printGetPointDown(index, j).__str__()
                            setPartDownTemp = printSetPointDown(index, j)
                        index = index + 1
    print up_down


class V8AccessVariableDeclarationWrapper(object):
    """
    About:
    """
    pass


def extract_variable_declaration(source, header_file_name):
    """
    Abstract:
        Extract variable declaration form C++ header file.
    Args:
        source - content header file
        header_file_name - name header file

    Returns:
        ...
    """
    builder = ast.BuilderFromSource(source, header_file_name)
    out_data = {}
    try:
        for node in builder.Generate():
            if isinstance(node, ast.Class):
                out_data[node.name] = []
                class_data = out_data[node.name]
                for record in node.body:
                    if isinstance(record, ast.VariableDeclaration):
                        class_data.append(record)
        return out_data
    except KeyboardInterrupt:
        return
    except Exception as e:
        pass


def main():
    #header_file_name = 'test-data/point.h'
    header_file_name = 'test-data/database.h'
    source = utils.ReadFile(header_file_name)

    make(source)

    """
    out_data = extract_variable_declaration(source, header_file_name)

    for class_name in out_data:
        print class_name
        for var in out_data[class_name]:
            print var.name"""


if __name__ == '__main__':
    main()


