# coding: utf-8
__author__ = 'Igor'

# App
from _v8_name_mapper import V8Decoders
from _utils import Util


class V8ScalarWrappers(object):
    @staticmethod
    def make_scalar_getter(var_type, name):
        result = \
            '\nstatic void v8_get_' + Util.get_fun_name_by_array_types(name)[0] + \
            '(\n      Local<String> name,\n' + \
            '      const PropertyCallbackInfo<Value>& info) \n    {\n' + \
            '    Local<Object> self = info.Holder();\n' + \
            '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
            '    void* ptr = wrap->Value();\n' + \
            '    ' + V8Decoders.unroll_unsigned_typedefs(var_type) + " value = static_cast<Point*>(ptr)->" \
            + name + ';\n' + \
            '    info.GetReturnValue().Set(' + V8Decoders.cpp_type_to_v8(var_type, "get") + '::New(value));\n}\n'
        return Util.clear_result(Util.is_array_(result, name, var_type, "get"))

    @staticmethod
    def make_scalar_setter(var_type, var_name):
        result = \
            "\n" + "static void v8_set_" + Util.get_fun_name_by_array_types(var_name)[0] \
            + '(\n      Local<String> property, \n      Local<Value> value,\n' + \
            '      const PropertyCallbackInfo<void>& info) \n    {\n' + \
            '    Local<Object> self = info.Holder();\n' + \
            '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
            '    void* ptr = wrap->Value();\n' + \
            '    static_cast<''' + "DataBase" + "*>(ptr)->" + var_name + "= value->" \
            + V8Decoders.cpp_type_to_v8(var_type, "set") + 'Value(); ' + \
            '\n}\n'
        return Util.clear_result(Util.is_array_(result, var_name, var_type, "set"))