# coding: utf-8

# std
import re

# App
from _v8_api.name_mapper import V8Decoders

# Печатать массивы?
# 0 - вывод без массивов!
# 1 - вывод с массивами (по умолчанию 0)
check_array_print = 0


def getFuncName(name):
    nameCapitalized = name.capitalize()
    return name.replace("_", "").replace(name[0], nameCapitalized[0]);


def make_scalar_getter(type, name):
    result = \
        "\n" + "static void v8_get_" + get_fun_name_by_array_types(name)[0] + """(Local<String> name,
    const PropertyCallbackInfo<Value>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  """ + V8Decoders.unroll_unsigned_typedefs(type) + " value = static_cast<Point*>(ptr)->" + name + ''';
  info.GetReturnValue().Set(''' + V8Decoders.cpp_type_to_v8(type, "get") + """::New(value));
}
"""
    return clear_result(ArrayOrNotArray(result, name, type, "get"))


def make_scalar_setter(type, name):
    result = \
        "\n" + "static void v8_set_" + get_fun_name_by_array_types(name)[0] \
        + '''(Local<String> property, Local<Value> value,
    const PropertyCallbackInfo<void>& info) {
  Local<Object> self = info.Holder();
  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
  void* ptr = wrap->Value();
  static_cast<''' + "DataBase" + "*>(ptr)->" + name + "= value->" + V8Decoders.cpp_type_to_v8(type, "set") \
        + "Value();" + '''
}
'''
    return clear_result(ArrayOrNotArray(result, name, type, "set"))


def get_fun_name_by_array_types(name):
    result = name
    index = ""
    regular = re.compile('\[.*')
    searchResult = regular.search(result)
    if searchResult:
        result = result.replace(searchResult.group(), "")
        index = searchResult.group()
    return result, index.replace("[", "").replace("]", "")


def make_array_index_getter_sample(type, name):
    result = "static void v8_get_array_index_" + get_fun_name_by_array_types(name)[0] \
             + """(uint32_t index,	const PropertyCallbackInfo<Value>& info) {
  if (index < """ + get_fun_name_by_array_types(name)[1] + """) {
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


def make_array_index_setter_sample(type, name):
    result = "static void v8_set_array_index_" + get_fun_name_by_array_types(name)[0] + """(
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
    result = "static void v8_get_array_" + get_fun_name_by_array_types(name)[0] + """(
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
  Handle<External> array_handle = External::New(database->""" + get_fun_name_by_array_types(name)[0] + """);
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
    result = ArrayOrNotArray(result, name, type, "add")
    # for arrays
    if "[" in name:
        result = "\n" + """
  result->SetAccessor(String::New(\"""" + get_fun_name_by_array_types(name)[0] + "\"), v8_get_array_" + \
                 get_fun_name_by_array_types(name)[0] + """);
  result->SetIndexedPropertyHandler(v8_get_array_index_""" + get_fun_name_by_array_types(name)[
                     0] + ", v8_set_array_index_" + get_fun_name_by_array_types(name)[0] + ");"
    return result


def ArrayOrNotArray(result, name, type, typeFunc):
    if check_array_print == 0:
        if "[" not in name and "vector" not in type:
            return result
        else:
            return ""
    if check_array_print == 1:
        if "[" not in name and "vector" not in type:
            return result
        else:
            return result
    if typeFunc == "add":
        return "error: bad logic (in make_getter_and_setter_add) or " \
               + check_array_print + " != 0 or 1, default = 0"
    if typeFunc == "set":
        return "error: bad logic (in make_scalar_setter) or " \
               + check_array_print + " != 0 or 1, default = 0"
    if typeFunc == "get":
        return "error: bad logic (in make_scalar_getter) or " \
               + check_array_print + " != 0 or 1, default = 0"


# ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
# еще добавил формирование функции CreateBlueprint
def make_scalars_and_accessors_with_formating(type_and_var_list):
    result = """v8::Handle<v8::ObjectTemplate> CreateBlueprint(
      v8::Isolate* isolate) {
"""
    for elem in type_and_var_list:
        result = result + make_getter_and_setter_add(*elem) + "\n"

    result += """\r\n}"""

    result = result.replace('\n\n', '\n')

    for elem in type_and_var_list:
        result = result + make_scalar_getter(*elem) + make_scalar_setter(*elem)

    result = result.replace('\n ', '\n')
    result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
    result = result.replace("}\n", "}\n\n").replace("\n\n\n", "\n\n")

    return result

