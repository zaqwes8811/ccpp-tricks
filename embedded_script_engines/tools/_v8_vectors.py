# coding: utf-8
__author__ = 'Igor'

# App
from _utils import Util
from _v8_scalars import V8ScalarWrappers


class V8ArraysWrapper(object):
    def __init__(self, var_type, var_name):
        self.var_type_ = var_name
        pass

    @staticmethod
    def __do_array_index_getter_sample(var_type, var_name):
        result = "static void v8_get_array_index_" \
                 + Util.get_fun_name_by_array_types(var_name)[0] + \
                 '(\n      uint32_t index, \n      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
                 '  if (index < ' \
                 + Util.get_fun_name_by_array_types(var_name)[1] + ') {\n' + \
                 '    v8::Local<v8::Object> self = info.Holder();\n' + \
                 '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
                 '    void* ptr = wrap->Value();\n' + \
                 '    int* ' + "database" + ' = static_cast<int*>(ptr);\n' + \
                 '    info.GetReturnValue().Set(' + "v8::Number::New(database[index])" + ');\n' + \
                 '  } else {\n' + \
                 '    info.GetReturnValue().Set(Undefined());\n' + \
                 '  }\n' + \
                 '}\n'
        return result

    @staticmethod
    def __do_array_index_setter_sample(var_type, var_name):
        result = "static void v8_set_array_index_" + Util.get_fun_name_by_array_types(var_name)[0] + '(\n' + \
                 '  uint32_t index,\n' + \
                 '  Local<Value> value,\n' + \
                 '    const PropertyCallbackInfo<Value>& info) {\n' + \
                 '}\n'
        return result

    #@Public:
    @staticmethod
    def make_array_index_getter(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.__do_array_index_getter_sample(var_type, name)
        return ""

    @staticmethod
    def make_array_index_setter(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.__do_array_index_setter_sample(var_type, name)
        else:
            return ""

    def make_array_getter(self, var_type, var_name):
        result = "static void v8_get_array_" \
                 + Util.get_fun_name_by_array_types(var_name)[0] + '(' + \
                 '      Local<String> name,\n' + \
                 '      const PropertyCallbackInfo<Value>& info) {\n' + \
                 '  Local<Object> self = info.Holder();\n' + \
                 '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
                 '  void* ptr = wrap->Value();\n' + \
                 '  SmallBase* database = static_cast<SmallBase*>(ptr);\n' + \
                 '  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(\n' + \
                 '    Isolate::GetCurrent(),\n' + \
                 '    var_array_blueprint_);\n' + \
                 '  Handle<Object> instance = templ->NewInstance();\n' + \
                 '  Handle<External> array_handle = External::New(database->' \
                 + Util.get_fun_name_by_array_types(var_name)[0] + ');\n' + \
                 '  instance->SetInternalField(0, array_handle);\n' + \
                 '  info.GetReturnValue().Set<v8::Object>(instance);\n' + \
                 '}\n'
        if "[" in var_name:
            return result
        else:
            return ""

    @staticmethod
    def make_getter_and_setter_add(var_type, name):
        # for scalars
        result = "  result->SetAccessor(String::New(\"" + name + "\"), v8_get_" + name + ", v8_set_" + name + ");"
        result = Util.is_array_(result, name, var_type, "add")

        # for arrays
        if "[" in name:
            result = "\n" + \
                     '  result->SetAccessor(String::New(\"' + \
                     Util.get_fun_name_by_array_types(name)[0] + "\"), v8_get_array_" + \
                     Util.get_fun_name_by_array_types(name)[0] + ');\n' + \
                     '  result->SetIndexedPropertyHandler(v8_get_array_index_' \
                     + Util.get_fun_name_by_array_types(name)[0] + \
                     ', v8_set_array_index_' + Util.get_fun_name_by_array_types(name)[0] + ");"
        return result


    # ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
    # еще добавил формирование функции CreateBlueprint
    @staticmethod
    def make_scalars_and_accessors_with_formating(type_and_var_list):
        result = 'v8::Handle<v8::ObjectTemplate> CreateBlueprint(\n' + \
                 '      v8::Isolate* isolate) {\n'
        for elem in type_and_var_list:
            result = result + V8ArraysWrapper.make_getter_and_setter_add(*elem) + "\n"

        result += '\n}'

        result = result.replace('\n\n', '\n')

        for elem in type_and_var_list:
            result = result + V8ScalarWrappers.make_scalar_getter(*elem) + V8ScalarWrappers.make_scalar_setter(*elem)

        result = result.replace('\n ', '\n')
        result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
        result = result.replace("}\n", "}\n\n").replace("\n\n\n", "\n\n")

        return result
