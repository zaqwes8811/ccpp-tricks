# coding: utf-8
__author__ = 'Igor'

# std
import sys

# App
import __v8_api.name_mapper as name_mapper
from __utils import Util


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
            '    ' + name_mapper.V8Decoders.unroll_unsigned_typedefs(var_type) + " value = static_cast<Point*>(ptr)->" \
            + name + ';\n' + \
            '    info.GetReturnValue().Set(' + name_mapper.V8Decoders.cpp_type_to_v8(var_type, "get") + '::New(value));\n}\n'
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
            + name_mapper.V8Decoders.cpp_type_to_v8(var_type, "set") + 'Value(); ' + \
            '\n}\n'
        return Util.clear_result(Util.is_array_(result, var_name, var_type, "set"))


# zaqwes
class ScalarVariableField(object):
    """
    About:
    """
    def is_array(self):
        """
        About:
            vector vec;
            int array[]
        """
        result = False
        if '[' in self.variable_node_.name or 'vector' in self.variable_node_.type.name:
            result = True

        return result

    def get_array_size(self):
        if self.is_array():
            return 0
        else:
            return None

    def __str__(self):
        return str(self.class_name_)

    def __init__(self, class_name, variable_node):
        #if not isinstance(variable_node, ast.VariableDeclaration):
        #    raise Exception("Only scalar field support support!")

        self.class_name_ = class_name
        self.variable_node_ = variable_node

        # Регистрируем типы
        self.V8_GETTER_RECODER_ = {'int': 'Integer', 'std::string': 'String', 'bool': 'Boolean'}
        self.V8_SETTER_RECODER_ = {'int': 'Int32', 'std::string': 'String', 'bool': 'Boolean'}

    def get_wrapper_class_name(self):
        return 'ForgeV8' + self.class_name_ + 's'

    def make_scalar_getter(self):
        """
        About:
        class Point {
            public:  // bad, but now be it
            int x;
        };

        Notes:
            static method is BAD!
        """
        field_type, field_name, class_name = (self.variable_node_.type.name,
                                              self.variable_node_.name,
                                              self.class_name_)

        if field_type not in self.V8_GETTER_RECODER_:
            return "// Map not found: " + field_type + ' - ' + field_name, None

        def make_getter_header(field_name_local):
            return 'void ' + self.get_wrapper_class_name() + '::v8_getter_' + field_name_local + '(\r\n' + \
                   '    v8::Local<v8::String> name,\r\n' + \
                   '    const v8::PropertyCallbackInfo<v8::Value>& info)'

        template = make_getter_header(field_name) + ' \r\n' + \
                   '  {\r\n' + \
                   '  Local<Object> self = info.Holder();\r\n' + \
                   '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\r\n' + \
                   '  void* ptr = wrap->Value();\r\n' + \
                   '  ' + field_type + ' value = static_cast<' + class_name + '*>(ptr)->' + field_name + ';\r\n' + \
                   '  info.GetReturnValue().Set(' + self.V8_GETTER_RECODER_[field_type] + '::New(value));\r\n' + \
                   '}'

        return template, make_getter_header(field_name) + ';\r\n'

    def make_scalar_setter(self):
        field_type, field_name, class_name = (self.variable_node_.type.name,
                                              self.variable_node_.name,
                                              self.class_name_)

        if field_type not in self.V8_GETTER_RECODER_:
            return "Map not found"

        template = 'void ' + self.get_wrapper_class_name() + '::v8_setter_' + field_name + '(\r\n' + \
                   '        Local<String> property, Local<Value> value,\r\n' + \
                   '        const PropertyCallbackInfo<void>& info) \r\n' + \
                   '  {\r\n' + \
                   '  Local<Object> self = info.Holder();\r\n' + \
                   '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\r\n' + \
                   '  void* ptr = wrap->Value();\r\n' + \
                   '  static_cast<' + class_name + '*>(ptr)->' + field_name + ' = value->' + self.V8_SETTER_RECODER_[
                       field_type] + 'Value();\r\n' + \
                   '}'

        return template


def make_header(impl_local, header):
    script_name = sys.argv[0]
    code_result = []
    class_name = impl_local[0][1]
    code_result.append('// Autogenerated by - ' + script_name)
    protect_directive = class_name.upper() + '_H_'
    code_result.append('#ifndef ' + protect_directive)
    code_result.append('#define ' + protect_directive + '\r\n')
    code_result.append('// Other')
    code_result.append('#include <v8.h>\r\n')
    code_result.append('#include "' + header + '"\r\n')
    code_result.append('//@StateLess\r\nclass ' + class_name + ' {')
    code_result.append(' public:')

    # Лучше передавать указатель, но тогда это не обертка, а генератор
    code_result.append(
        '  ' + class_name + '() { }\r\n')
    code_result.append('  // TODO: It need be impl. manual')
    code_result.append('  v8::Handle<v8::Object> Forge_NI(\r\n      '
                       'Point* point, \r\n      ' +
                       'v8::Isolate* isolate,\r\n      ' +
                       'v8::Persistent<v8::ObjectTemplate>* blueprint);\r\n')
    code_result.append('  // TODO: It need be impl. manual')
    code_result.append('  v8::Handle<v8::ObjectTemplate> MakeBlueprint_NI(v8::Isolate* isolate);\r\n')

    for impl in impl_local:
        code_result.append('  static ' + impl[0])
    code_result.append('};')
    code_result.append('#endif')
    return code_result


def make_source(impls_local, header_name):
    script_name = sys.argv[0]
    code_result = []
    class_name = impls_local[0][1]
    code_result.append('// Autogenerated by - ' + script_name + '\r\n')
    code_result.append('//#include "app/config.h"  // TODO: Need impl.')
    code_result.append('#include "' + header_name + '"  // TODO: Need connect real.\r\n')
    code_result.append('// C++')
    code_result.append('#include <string>\r\n')
    code_result.append('using std::string;\r\n')
    code_result.append('using v8::Object;')
    code_result.append('using v8::Handle;')
    code_result.append('using v8::Local;')
    code_result.append('using v8::Value;')
    code_result.append('using v8::ObjectTemplate;')
    code_result.append('using v8::External;')
    code_result.append('using v8::Context;')
    code_result.append('using v8::Isolate;')
    code_result.append('using v8::Persistent;')
    code_result.append('using v8::Integer;')
    code_result.append('using v8::String;')
    code_result.append('\r\n')

    for impl in impls_local:
        code_result.append(impl[0] + '\r\n')

    return code_result


def append_maker_bp_and_forge(code_result, class_name):
    # Add code
    # Need be impl.
    code_result.append('\r\n// TODO: It need be impl. manual')
    code_result.append('v8::Handle<v8::Object> ' + class_name + '::Forge_NI(\r\n      '
                                                                'Point* point, \r\n      ' +
                       'v8::Isolate* isolate,\r\n      ' +
                       'v8::Persistent<v8::ObjectTemplate>* blueprint) { \r\n\r\n}\r\n')
    code_result.append('// TODO: It need be impl. manual')

    impl_maker_blueprint = '{ \r\n\r\n}'
    code_result.append('v8::Handle<v8::ObjectTemplate> ' + class_name + '::MakeBlueprint_NI(v8::Isolate* isolate) ' +
                       impl_maker_blueprint + '\r\n')

    for var in None:
        var_name = var.variable_node_.name
        if var_name == '???':
            # Возникает, если поля - массивы.
            # Но если размер задан - он присоединяется к имени, и для 2D тоже
            #   потом их не разделить.
            if var.variable_node_.type.array:
                print var.variable_node_.type.modifiers[0]
                print var.variable_node_.type.name
            print var.variable_node_
        else:
            # Scalars
            print var_name