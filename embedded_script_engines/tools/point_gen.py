# coding: utf-8
import re  # регулярные выражения

# std
import sys

# Third_party
from generator.cpp import utils

# App
from _units import extract_variable_declaration
from _units import make_header
from _units import make_source


def write_source(file_name, code):
    f = open(file_name, 'w')
    f.write(('\r\n'.join(code))
        .replace('\r', '@')
        .replace('@', ''))
    f.close()


def main():
    header_file_name = '../v8/src/point.h'
    #header_file_name = './test-data/point.h'
    source = utils.ReadFile(header_file_name)

    # zaqwes
    vars_ = extract_variable_declaration(source, header_file_name)

    #if
    # Make V8 view
    impls = []
    declarations = []

    for elem in vars_:
        i, d = elem.make_scalar_getter()
        if d:
            impls.append((i, elem.get_wrapper_class_name()))
            declarations.append((d, elem.get_wrapper_class_name()))
        else:
            print i

    code = make_header(declarations, 'point.h')
    header_name = 'forge_v8_point.h'
    write_source(header_name, code)
    code = make_source(impls, header_name)

    def append_maker_bp_and_forge(code_result):
        # Add code
        # Need be impl.
        code_result.append('\r\n// TODO: It need be impl. manual')
        code_result.append('v8::Handle<v8::Object> '+class_name+'::Forge_NI(\r\n      '
                           'Point* point, \r\n      ' +
                           'v8::Isolate* isolate,\r\n      ' +
                           'v8::Persistent<v8::ObjectTemplate>* blueprint) { \r\n\r\n}\r\n')
        code_result.append('// TODO: It need be impl. manual')

        impl_maker_blueprint = '{ \r\n\r\n}'
        code_result.append('v8::Handle<v8::ObjectTemplate> '+class_name+'::MakeBlueprint_NI(v8::Isolate* isolate) '+
                           impl_maker_blueprint+'\r\n')

    for var in vars_:
        var_name = var.variable_node_.name
        if var_name == '???':
            if var.variable_node_.type.array:
                print var.variable_node_.type.modifiers[0]
                print var.variable_node_.type.name
            print var.variable_node_
        else:
            # Scalars
            print var_name

    # Итоговый исходник
    write_source('forge_v8_point.cc', code)



if __name__ == '__main__':
    main()


