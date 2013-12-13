# coding: utf-8

# Third_party
from generator.cpp import utils

# App
from generators_cpp_code.v8_api_gen import scalars
from parsers_cpp_code import header_parser
import utils_local


def main():
    def extract_variable_declaration(source_):
        """
        Args:
            source - string with code
        """
        type_and_var_list = header_parser.Holder.extract_var_declaration(source_)
        result = []
        for var in type_and_var_list:
            result.append(scalars.ScalarVariableField('unknown', header_parser.VarDeclaration(*var)))

        return result

    header_file_name = 'idata/sampler.h'
    source = utils.ReadFile(header_file_name)

    # zaqwes
    vars_ = extract_variable_declaration(source)

    #if
    # Make V8 view
    impls = []
    declarations = []

    for elem in vars_:
        if elem.is_array():
            print 'is array'
        else:
            i, d = elem.make_scalar_getter()
            if d:
                impls.append((i, elem.get_wrapper_class_name()))
                declarations.append((d, elem.get_wrapper_class_name()))
            else:
                print i

    code = scalars.make_header(declarations, 'point.h')
    header_name = 'odata/forge_v8_point.h'
    utils_local.write_source(header_name, code)
    code = scalars.make_source(impls, header_name)

    # Итоговый исходник
    utils_local.write_source('odata/forge_v8_point.cc', code)


if __name__ == '__main__':
    main()


