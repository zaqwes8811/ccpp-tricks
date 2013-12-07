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
            '\nstatic void v8_get_' + Util_.get_fun_name_by_array_types(name)[0] + \
            '(\n      Local<String> name,\n' + \
            '      const PropertyCallbackInfo<Value>& info) \n    {\n' + \
            '    Local<Object> self = info.Holder();\n' + \
            '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
            '    void* ptr = wrap->Value();\n' + \
            '    ' + V8Decoders.unroll_unsigned_typedefs(var_type) + " value = static_cast<Point*>(ptr)->" \
            + name + ';\n' + \
            '    info.GetReturnValue().Set(' + V8Decoders.cpp_type_to_v8(var_type, "get") + '::New(value));\n}\n'
        return Util_.clear_result(Util_.is_array_(result, name, var_type, "get"))

    @staticmethod
    def make_scalar_setter(var_type, var_name):
        result = \
            "\n" + "static void v8_set_" + Util_.get_fun_name_by_array_types(var_name)[0] \
            + '(\n      Local<String> property, \n      Local<Value> value,\n' + \
            '      const PropertyCallbackInfo<void>& info) \n    {\n' + \
            '    Local<Object> self = info.Holder();\n' + \
            '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
            '    void* ptr = wrap->Value();\n' + \
            '    static_cast<''' + "DataBase" + "*>(ptr)->" + var_name + "= value->" \
            + V8Decoders.cpp_type_to_v8(var_type, "set") + 'Value(); ' + \
            '\n}\n'
        return Util_.clear_result(Util_.is_array_(result, var_name, var_type, "set"))


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

    @staticmethod
    def clear_result(result):
        result = result.replace('\n ', '\n').replace("\n\n\n", "")
        result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
        result = result.replace("}\n", "}\n\n").replace("}\n\n}", "}\n}").replace("}\n\n\n", "}\n\n")
        return result


class V8ArraysWrapper(object):
    @staticmethod
    def make_array_index_getter_sample(var_type, var_name):
        result = "static void v8_get_array_index_" \
                 + Util_.get_fun_name_by_array_types(var_name)[0] + \
                 '(\n      uint32_t index, \n      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
                 '  if (index < ' \
                 + Util_.get_fun_name_by_array_types(var_name)[1] + ') {\n' + \
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
    def make_array_index_setter_sample(var_type, var_name):
        result = "static void v8_set_array_index_" + Util_.get_fun_name_by_array_types(var_name)[0] + '(\n' + \
                 '  uint32_t index,\n' + \
                 '  Local<Value> value,\n' + \
                 '    const PropertyCallbackInfo<Value>& info) {\n' + \
                 '}\n'
        return result

    @staticmethod
    def make_array_index_getter_func(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.make_array_index_getter_sample(var_type, name)
        return ""

    @staticmethod
    def make_array_index_setter_func(var_type, name):
        if "[" in name:
            return V8ArraysWrapper.make_array_index_setter_sample(var_type, name)
        else:
            return ""

    @staticmethod
    def make_array_index_getter(var_type, name):
        return V8ArraysWrapper.make_array_index_getter_func(var_type, name)

    @staticmethod
    def make_array_index_setter(var_type, name):
        return V8ArraysWrapper.make_array_index_setter_func(var_type, name)

    @staticmethod
    def make_array_getter(var_type, var_name):
        result = "static void v8_get_array_" \
                 + Util_.get_fun_name_by_array_types(var_name)[0] + '(' + \
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
                 + Util_.get_fun_name_by_array_types(var_name)[0] + ');\n' + \
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
        result = Util_.is_array_(result, name, var_type, "add")

        # for arrays
        if "[" in name:
            result = "\n" + \
                     '  result->SetAccessor(String::New(\"' + \
                     Util_.get_fun_name_by_array_types(name)[0] + "\"), v8_get_array_" + \
                     Util_.get_fun_name_by_array_types(name)[0] + ');\n' + \
                     '  result->SetIndexedPropertyHandler(v8_get_array_index_' \
                     + Util_.get_fun_name_by_array_types(name)[0] + \
                     ', v8_set_array_index_' + Util_.get_fun_name_by_array_types(name)[0] + ");"
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


if __name__ == '__main__':
    def main():
        class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
        type_and_var_list = Holder.extract_var_declaration(class_transmit_code)
        # такой будет вывод, когда подключим все массивы и функции
        if False:
            for elem in type_and_var_list:
                print(V8ArraysWrapper.make_getter_and_setter_add(*elem))

            for elem in type_and_var_list:
                print(V8ScalarWrappers.make_scalar_getter(*elem))
                print(V8ScalarWrappers.make_scalar_setter(*elem))
        else:
        # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
            # scalars and accessors in blueprint
            print(V8ArraysWrapper.make_scalars_and_accessors_with_formating(type_and_var_list))
            # arrays
            for elem in type_and_var_list:
                print(V8ArraysWrapper.make_array_index_getter(*elem))
                print(V8ArraysWrapper.make_array_index_setter(*elem))
                print(V8ArraysWrapper.make_array_getter(*elem))

    main()


