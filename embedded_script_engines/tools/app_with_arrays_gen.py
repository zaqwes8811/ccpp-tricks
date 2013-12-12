# coding: utf-8

# Other
from generator.cpp import utils

# App
from __cpp_code_parsers import header_parser
from _v8_api import scalars
from _v8_api import vectors

if __name__ == '__main__':
    def main():
        class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
        type_and_var_list = header_parser.Holder.extract_var_declaration(class_transmit_code)

        builder = vectors.BuilderArrayWrapper(type_and_var_list)

        for impl in builder.get_zero_level_accessors_header():
            print impl

    main()


