# coding: utf-8
__author__ = 'Igor'

# App
import app_utils
from _v8_api import scalars


class V8ArraysWrapper(object):
    def __init__(self, var_type, var_name):
        self.var_type_ = var_name
        pass

    @staticmethod
    def __do_getter_by_idx_int(var_type, var_name, class_name='database'):
        result = "static void v8_get_array_index_" \
                 + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + \
                 '(\n      uint32_t index, \n      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
                 '  if (index < ' \
                 + app_utils.Util.build_accessor_name_by_array_name(var_name)[1] + ') {\n' + \
                 '    v8::Local<v8::Object> self = info.Holder();\n' + \
                 '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
                 '    void* ptr = wrap->Value();\n' + \
                 '    int* array = static_cast<int*>(ptr);\n' + \
                 '    info.GetReturnValue().Set(v8::Number::New(array[index])' + ');\n' + \
                 '  } else {\n' + \
                 '    info.GetReturnValue().Set(Undefined());\n' + \
                 '  }\n' + \
                 '}\n'
        return result

    @staticmethod
    def __do_setter_by_idx_NI(var_type, var_name):
        result = "static void v8_set_array_index_" \
                 + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + '(\n' + \
                 '  uint32_t index,\n' + \
                 '  Local<Value> value,\n' + \
                 '    const PropertyCallbackInfo<Value>& info) {\n' + \
                 '}\n'
        return result

    #@Public:
    @staticmethod
    def make_array_index_getter(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.__do_getter_by_idx_int(var_type, name)
        return ""

    @staticmethod
    def make_array_index_setter(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.__do_setter_by_idx_NI(var_type, name)
        else:
            return ""

    def make_array_getter(self, var_type, var_name):
        result = "static void v8_get_array_" \
                 + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + '(' + \
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
                 + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + ');\n' + \
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
        result = app_utils.Util.is_array(result, name, var_type, "add")

        # for arrays
        if "[" in name:
            result = "\n" + \
                     '  result->SetAccessor(String::New(\"' + \
                     app_utils.Util.build_accessor_name_by_array_name(name)[0] + "\"), v8_get_array_" + \
                     app_utils.Util.build_accessor_name_by_array_name(name)[0] + ');\n' + \
                     '  result->SetIndexedPropertyHandler(v8_get_array_index_' \
                     + app_utils.Util.build_accessor_name_by_array_name(name)[0] + \
                     ', v8_set_array_index_' + app_utils.Util.build_accessor_name_by_array_name(name)[0] + ");"
        return result

    @staticmethod
    def make_scalars_and_accessors_with_formating(type_and_var_list):
        # ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
        # еще добавил формирование функции CreateBlueprint
        result = 'v8::Handle<v8::ObjectTemplate> CreateBlueprint(\n' + \
                 '      v8::Isolate* isolate) {\n'
        for elem in type_and_var_list:
            result = result + V8ArraysWrapper.make_getter_and_setter_add(*elem) + "\n"

        result += '\n}'

        result = result.replace('\n\n', '\n')

        for elem in type_and_var_list:
            result = result + scalars.V8ScalarWrappers.make_scalar_getter(*elem) \
                     + scalars.V8ScalarWrappers.make_scalar_setter(*elem)

        result = result.replace('\n ', '\n')
        result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
        result = result.replace("}\n", "}\n\n").replace("\n\n\n", "\n\n")

        return result
