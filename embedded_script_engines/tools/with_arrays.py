# coding: utf-8
import re  # регулярные выражения

# Other
from generator.cpp import utils

# App
from _h_parser import Holder, VarDeclaration
from _v8_name_mapper import V8Decoders

# 0 - нет
# 1 - да
# 0 - вывод без массивов!
# 1 - вывод с массивами (по умолчанию 0)
check_array_print = 0


class V8ScalarWrappers(object):
    @staticmethod
    def make_scalar_getter(var_type, name):
        result = \
            '\nstatic void v8_get_' + Util_.get_fun_name_by_array_types(name)[0] + '(Local<String> name,' + \
            '    const PropertyCallbackInfo<Value>& info) {' + \
            '  Local<Object> self = info.Holder();' + \
            '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));' + \
            '  void* ptr = wrap->Value();' + \
            '  ' + V8Decoders.unroll_unsigned_typedefs(var_type) + " value = static_cast<Point*>(ptr)->" \
            + name + ';' + \
            '  info.GetReturnValue().Set(' + V8Decoders.cpp_type_to_v8(var_type, "get") + '::New(value));\n}'
        return clear_result(Util_.is_array_(result, name, var_type, "get"))

    @staticmethod
    def make_scalar_setter(var_type, var_name):
        result = \
            "\n" + "static void v8_set_" + Util_.get_fun_name_by_array_types(var_name)[0] \
            + '(Local<String> property, Local<Value> value,' + \
            '    const PropertyCallbackInfo<void>& info) {' + \
            '  Local<Object> self = info.Holder();' + \
            '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));' + \
            '  void* ptr = wrap->Value();' + \
            '  static_cast<''' + "DataBase" + "*>(ptr)->" + var_name + "= value->" \
            + V8Decoders.cpp_type_to_v8(var_type, "set") + \
            '        "Value(); ' + \
            '}'
        return clear_result(Util_.is_array_(result, var_name, var_type, "set"))


class Util_(object):
    @staticmethod
    def get_fun_name_by_array_types(name):
        result = name
        index = ""
        regular = re.compile('\[.*')
        search_result = regular.search(result)
        if search_result:
            result = result.replace(search_result.group(), "")
            index = search_result.group()
        index = index.replace("[", "").replace("]", "")
        return result, index

    @staticmethod
    def is_array_(result, name, var_type, function_type):
        if check_array_print == 0:
            if "[" not in name and "vector" not in var_type:
                return result
            else:
                return ""
        if check_array_print == 1:
            if "[" not in name and "vector" not in var_type:
                return result
            else:
                return result
        if function_type == "add":
            return "error: bad logic (in make_getter_and_setter_add) or " \
                   + check_array_print + " != 0 or 1, default = 0"
        if function_type == "set":
            return "error: bad logic (in make_scalar_setter) or " \
                   + check_array_print + " != 0 or 1, default = 0"
        if function_type == "get":
            return "error: bad logic (in make_scalar_getter) or " \
                   + check_array_print + " != 0 or 1, default = 0"


def make_array_index_getter_sample(var_type, name):
    result = "static void v8_get_array_index_" + Util_.get_fun_name_by_array_types(name)[0] + \
             """(uint32_t index,	const PropertyCallbackInfo<Value>& info) {
  if (index < """ + Util_.get_fun_name_by_array_types(name)[1] + """) {
    v8::Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    int* """ + "database" + """ = static_cast<int*>(ptr);
    info.GetReturnValue().Set( """ + "v8::Number::New(database[index])" + """);
  } else {
    info.GetReturnValue().Set(Undefined());
  }
}"""
    return result


def make_array_index_setter_sample(var_type, name):
    result = "static void v8_set_array_index_" + Util_.get_fun_name_by_array_types(name)[0] + """(
  uint32_t index,
  Local<Value> value,
  const PropertyCallbackInfo<Value>& info) {
}"""
    return result


def make_array_index_getter_func(type, name):
    if "[" in name:
        return make_array_index_getter_sample(type, name)
    return ""


def make_array_index_setter_func(type, name):
    if "[" in name:
        return make_array_index_setter_sample(type, name)
    else:
        return ""


def make_array_index_getter(type, name):
    return make_array_index_getter_func(type, name)


def make_array_index_setter(type, name):
    return make_array_index_setter_func(type, name)


def make_array_getter(type, name):
    result = "static void v8_get_array_" + Util_.get_fun_name_by_array_types(name)[0] + """(
      Local<String> name,
      const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  SmallBase* database = static_cast<SmallBase*>(ptr);
  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(
    Isolate::GetCurrent(),
    var_array_blueprint_);
  Handle<Object> instance = templ->NewInstance();
  Handle<External> array_handle = External::New(database->""" + Util_.get_fun_name_by_array_types(name)[0] + """);
  instance->SetInternalField(0, array_handle);
  info.GetReturnValue().Set<v8::Object>(instance);
}"""
    if "[" in name:
        return result
    else:
        return ""


def clear_result(result):
    result = result.replace('\n ', '\n').replace("\n\n\n", "")
    result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
    result = result.replace("}\n", "}\n\n").replace("}\n\n}", "}\n}").replace("}\n\n\n", "}\n\n")
    return result


def make_getter_and_setter_add(type, name):
    # for scalars
    result = "  result->SetAccessor(String::New(\"" + name + "\"), v8_get_" + name + ", v8_set_" + name + ");"
    result = Util_.is_array_(result, name, type, "add")
    # for arrays
    if "[" in name:
        result = "\n" + """
  result->SetAccessor(String::New(\"""" \
                 + Util_.get_fun_name_by_array_types(name)[0] + "\"), v8_get_array_" \
                 + Util_.get_fun_name_by_array_types(name)[0] + """);
  result->SetIndexedPropertyHandler(v8_get_array_index_""" \
                 + Util_.get_fun_name_by_array_types(name)[0] + \
                 ", v8_set_array_index_" + Util_.get_fun_name_by_array_types(name)[0] + ");"
    return result





# ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
# еще добавил формирование функции CreateBlueprint
def make_scalars_and_accessors_with_formating(type_and_var_list):
    result = """v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate) {
"""
    for elem in type_and_var_list:
        result = result + make_getter_and_setter_add(*elem) + "\n"

    result = result + """
}"""

    result = result.replace('\n\n', '\n')

    for elem in type_and_var_list:
        result = result + V8ScalarWrappers.make_scalar_getter(*elem) + V8ScalarWrappers.make_scalar_setter(*elem)

    result = result.replace('\n ', '\n')
    result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
    result = result.replace("}\n", "}\n\n").replace("\n\n\n", "\n\n")

    return result


if __name__ == '__main__':
    class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
    type_and_var_list = Holder.extract_var_declaration(class_transmit_code)
    # такой будет вывод, когда подключим все массивы и функции
    if False:
        for elem in type_and_var_list:
            print(make_getter_and_setter_add(*elem))

        for elem in type_and_var_list:
            print(V8ScalarWrappers.make_scalar_getter(*elem))
            print(V8ScalarWrappers.make_scalar_setter(*elem))
    else:
    # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
        # scalars and accessors in blueprint
        print(make_scalars_and_accessors_with_formating(type_and_var_list))
        # arrays
        for elem in type_and_var_list:
            print(make_array_index_getter(*elem))
            print(make_array_index_setter(*elem))
            print(make_array_getter(*elem))


