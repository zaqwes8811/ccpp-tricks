# coding: utf-8
import re  # регулярные выражения

# Third_party
from generator.cpp import utils
from generator.cpp import ast

from han import extract_var_declaration
from han import make_scalar_getter, make_scalar_setter
from han import make_getter_and_setter_add
from han import makeAll


class ScalarVariableField(object):
    """
    About:
    """

    def __init__(self, class_name, variable_node):
        #if not isinstance(variable_node, ast.VariableDeclaration):
        #    raise Exception("Only scalar field support support!")

        self.class_name_ = class_name
        self.variable_node_ = variable_node

        # Регистрируем типы
        self.V8_GETTER_RECODER_ = {'int': 'Integer', 'std::string': 'String'}
        self.V8_SETTER_RECODER_ = {'int': 'Int32', 'std::string': 'String'}

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
            return "Map not found"

        template = 'void v8_getter_' + field_name + '(\r\n' + \
                   '    Local<String> name,\r\n' + \
                   '    const PropertyCallbackInfo<Value>& info) \r\n' + \
                   '  {\r\n' + \
                   '  Local<Object> self = info.Holder();\r\n' + \
                   '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\r\n' + \
                   '  void* ptr = wrap->Value();\r\n' + \
                   '  ' + field_type + ' value = static_cast<' + class_name + '*>(ptr)->' + field_name + ';\r\n' + \
                   '  info.GetReturnValue().Set(' + self.V8_GETTER_RECODER_[field_type] + '::New(value));\r\n' + \
                   '}'

        return template

    def make_scalar_setter(self):
        field_type, field_name, class_name = (self.variable_node_.type.name,
                                              self.variable_node_.name,
                                              self.class_name_)

        if field_type not in self.V8_GETTER_RECODER_:
            print field_type
            return "Map not found"

        template = 'void v8_setter_' + field_name + '(\r\n' + \
                   '        Local<String> property, Local<Value> value,\r\n' + \
                   '        const PropertyCallbackInfo<void>& info) \r\n' + \
                   '  {\r\n' + \
                   '  Local<Object> self = info.Holder();\r\n' + \
                   '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\r\n' + \
                   '  void* ptr = wrap->Value();\r\n' + \
                   '  static_cast<' + class_name + '*>(ptr)->' + field_name + ' = value->' + self.V8_SETTER_RECODER_[field_type] + 'Value();\r\n' + \
                   '}'

        return template


def extract_variable_declaration(source, header_file_name):
    """
    Abstract:
        Extract variable declaration form C++ header file.
    Args:
        source - content header file
        header_file_name - name header file

    Returns:
        [VarField0, ...]
    """
    builder = ast.BuilderFromSource(source, header_file_name)
    try:
        for node in builder.Generate():
            if isinstance(node, ast.Class):
                for record in node.body:
                    if isinstance(record, ast.VariableDeclaration):
                        # модификаторы и... *, & отделены от имени типа!
                        #if scalar?:
                        #elif  vector? std::vector<string>, Vector, List, Array...
                        # это не скаляр и сеттер будет другим https://developers.google.com/v8/embed
                        #else
                        #check what happened
                        yield ScalarVariableField(node.name, record)
    except KeyboardInterrupt:
        return
    except Exception as e:
        pass


def main():
    header_file_name = 'test-data/point.h'
    #header_file_name = 'test-data/database.h'
    source = utils.ReadFile(header_file_name)

    if False:
        # han
        type_and_var_list = extract_var_declaration(source)

        if True:
            # временный вывод !отформатированный и без массивов!
            #print(makeAll(type_and_var_list))
            for elem in type_and_var_list:
                print type_and_var_list
        else:
            # формирование кода добавления геттеров и сеттеров
            for elem in type_and_var_list:
                print(make_getter_and_setter_add(*elem))

            for elem in type_and_var_list:
                print(make_scalar_getter(*elem))
                print(make_scalar_setter(*elem))
    else:
        # zaqwes
        vars = extract_variable_declaration(source, header_file_name)

        #if
        # Make V8 view
        for elem in vars:
            print(elem.make_scalar_getter())
            print(elem.make_scalar_setter())
        #elif Dart


if __name__ == '__main__':
    main()


