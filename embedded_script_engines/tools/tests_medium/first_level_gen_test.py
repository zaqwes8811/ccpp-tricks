# coding: utf-8

# Third_party
from generator.cpp import utils

# App
from generators_cpp_code.v8_api_gen import scalars
from parsers_cpp_code import header_parser
import utils_local


def main():
    header_file_name = 'idata/sampler.h'
    source = utils.ReadFile(header_file_name)
    class_name = "SomeThing"

    dec_wrappers = header_parser.extract_variable_declaration_own(source, class_name)
    code = scalars.make_scalar_setter_header(dec_wrappers)
    for line in code:
        print line


    '''
    header_name = 'odata/forge_v8_point.h'
    utils_local.write_source(header_name, code)

    code = scalars.make_source(impls, header_name)

    # Итоговый исходник
    utils_local.write_source('odata/forge_v8_point.cc', code)'''


if __name__ == '__main__':
    main()


