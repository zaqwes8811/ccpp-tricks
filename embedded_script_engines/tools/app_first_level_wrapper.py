# coding: utf-8

# std


# Third_party
from generator.cpp import utils

# App
from _v8_api._units_zaqwes import extract_variable_declaration
from _v8_api._units_zaqwes import make_header
from _v8_api._units_zaqwes import make_source
from _h_parser import Holder, VarDeclaration


def write_source(file_name, code):
    f = open(file_name, 'w')
    f.write(('\r\n'.join(code))
            .replace('\r', '@')
            .replace('@', ''))
    f.close()


def main():
    header_file_name = '../v8/src/point.h'
    header_file_name = './test-data/real_test_file.h'
    source = utils.ReadFile(header_file_name)

    # zaqwes
    #vars_ = extract_variable_declaration(source, header_file_name)
    vars_ = extract_variable_declaration(source)

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

    code = make_header(declarations, 'point.h')
    header_name = 'odata/forge_v8_point.h'
    write_source(header_name, code)
    code = make_source(impls, header_name)

    # Итоговый исходник
    write_source('odata/forge_v8_point.cc', code)


def extract_variable_declaration(source):
    """
    Args:
        source - string with code
    """
    from _v8_api._units_zaqwes import ScalarVariableField

    type_and_var_list = Holder.extract_var_declaration(source)
    result = []
    for var in type_and_var_list:
        result.append(ScalarVariableField('unknown', VarDeclaration(*var)))

    return result


if __name__ == '__main__':
    main()


