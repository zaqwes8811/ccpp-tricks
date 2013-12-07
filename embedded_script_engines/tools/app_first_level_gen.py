# coding: utf-8

# Third_party
from generator.cpp import utils

# App
from __cpp_code_parsers import header_parser
from _v8_api import scalars
import app_utils


def main():
    header_file_name = '../v8/src/point.h'
    header_file_name = './test-data/real_test_file.h'
    source = utils.ReadFile(header_file_name)

    # zaqwes
    vars_ = header_parser.extract_variable_declaration(source, header_file_name)
    #vars_ = __cpp_code_parsers.header_parser.extract_variable_declaration(source)

    #if
    # Make V8 view
    impls = []
    declarations = []

    for elem in vars_:
        if elem.is_array():
            pass
        else:
            i, d = elem.make_scalar_getter()
            if d:
                impls.append((i, elem.get_wrapper_class_name()))
                declarations.append((d, elem.get_wrapper_class_name()))
            else:
                print i

    code = scalars.make_header(declarations, 'point.h')
    header_name = 'odata/forge_v8_point.h'
    app_utils.write_source(header_name, code)
    code = scalars.make_source(impls, header_name)

    # Итоговый исходник
    app_utils.write_source('odata/forge_v8_point.cc', code)


def extract_variable_declaration(source):
    """
    Args:
        source - string with code
    """
    type_and_var_list = header_parser.Holder.extract_var_declaration(source)
    result = []
    for var in type_and_var_list:
        result.append(scalars.ScalarVariableField('unknown', header_parser.VarDeclaration(*var)))

    return result


if __name__ == '__main__':
    main()


