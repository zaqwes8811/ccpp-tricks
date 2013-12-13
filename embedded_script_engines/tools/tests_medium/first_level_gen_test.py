# coding: utf-8

# Third_party
from generator.cpp import utils

# App
from generators_cpp_code.v8_api_gen import scalars
from parsers_cpp_code import header_parser
import utils_local


def make_scalar_accessor_header(dec_wrappers):
    # zaqwes
    impls = []
    declarations = []
    for elem in dec_wrappers:
        if not elem.is_array():
            i, d = elem.make_scalar_getter()
            if d:
                impls.append((i, elem.get_wrapper_class_name()))
                declarations.append((d, elem.get_wrapper_class_name()))
            else:
                print i

    code = scalars.make_scalar_getters_header(declarations)
    return code


def main():
    header_file_name = 'idata/sampler.h'
    source = utils.ReadFile(header_file_name)
    class_name = "SomeThing"

    dec_wrappers = header_parser.extract_variable_declaration_own(source, class_name)
    code = make_scalar_accessor_header(dec_wrappers)


    '''
    header_name = 'odata/forge_v8_point.h'
    utils_local.write_source(header_name, code)

    code = scalars.make_source(impls, header_name)

    # Итоговый исходник
    utils_local.write_source('odata/forge_v8_point.cc', code)'''


if __name__ == '__main__':
    main()


