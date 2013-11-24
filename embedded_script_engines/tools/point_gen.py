# coding: utf-8
import re  # регулярные выражения

# Third_party
from generator.cpp import utils
from generator.cpp import ast

class ScalarVariableField(object):
    """
    About:
    """

    def __init__(self, class_name, variable_node):
        #if not isinstance(variable_node, ast.VariableDeclaration):
        #    raise Exception("Only scalar field support support!")

        self.class_name_ = class_name
        self.variable_node_ = variable_node

    @staticmethod
    def make_scalar_getter_template(field_type, field_name, class_name):
        """
        About:
        class Point {
            public:  // bad, but now be it
            int x;
        };

        Notes:
            static method is BAD!
        """

        v8_recoder = {'int': 'Integer', 'std::string': 'String'}
        if field_type not in v8_recoder:
            return "Map not found"

        template = 'void v8_getter_' + field_name + '(\r\n' + \
                   '      Local<String> name,\r\n' + \
                   '      const PropertyCallbackInfo<Value>& info) \r\n' + \
                   '  {\r\n' + \
                   '  Local<Object> self = info.Holder();\r\n' + \
                   '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\r\n' + \
                   '  void* ptr = wrap->Value();\r\n' + \
                   '  ' + field_type + ' value = static_cast<' + class_name + '*>(ptr)->' + field_name + ';\r\n' + \
                   '  info.GetReturnValue().Set(' + v8_recoder[field_type] + '::New(value));\r\n' + \
                   '}'

        return template

    def __str__(self):
        package = (self.variable_node_.type.name, self.variable_node_.name, self.class_name_)
        return ScalarVariableField.make_scalar_getter_template(*package)


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
    out_data = []
    try:
        for node in builder.Generate():
            if isinstance(node, ast.Class):
                for record in node.body:
                    if isinstance(record, ast.VariableDeclaration):
                        out_data.append(ScalarVariableField(node.name, record))
        return out_data
    except KeyboardInterrupt:
        return
    except Exception as e:
        pass


def main():
    header_file_name = 'test-data/point.h'
    #header_file_name = 'test-data/database.h'
    source = utils.ReadFile(header_file_name)

    #make(source)

    out_data = extract_variable_declaration(source, header_file_name)

    # модификаторы и... *, & отделены от имени типа!
    for elem in out_data:
        #if scalar?:

        print elem
        #elif  vector?
        #else
        #check what happened


if __name__ == '__main__':
    main()


