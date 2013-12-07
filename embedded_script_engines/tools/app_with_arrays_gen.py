# coding: utf-8

# Other
from generator.cpp import utils

# App
from __cpp_code_parsers import header_parser
from __v8_api import scalars
from __v8_api import vectors

if __name__ == '__main__':
    def main():
        class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
        type_and_var_list = header_parser.Holder.extract_var_declaration(class_transmit_code)
        # такой будет вывод, когда подключим все массивы и функции
        if False:
            for elem in type_and_var_list:
                print(vectors.V8ArraysWrapper.make_getter_and_setter_add(*elem))

            for elem in type_and_var_list:
                print(scalars.V8ScalarWrappers.make_scalar_getter(*elem))
                print(scalars.V8ScalarWrappers.make_scalar_setter(*elem))
        else:
            array_wrapper = vectors.V8ArraysWrapper(0, 0)
            # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
            # scalars and accessors in blueprint
            print(vectors.V8ArraysWrapper.make_scalars_and_accessors_with_formating(type_and_var_list))
            # arrays
            for elem in type_and_var_list:
                print(vectors.V8ArraysWrapper.make_array_index_getter(*elem))
                print(vectors.V8ArraysWrapper.make_array_index_setter(*elem))
                print(array_wrapper.make_array_getter(*elem))

    main()


