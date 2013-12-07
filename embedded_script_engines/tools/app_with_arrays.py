# coding: utf-8

# Other
from generator.cpp import utils

# App
from __cpp_code_parsers.header_parser import Holder
from __v8_api.scalars import V8ScalarWrappers
from __v8_api.vectors import V8ArraysWrapper

if __name__ == '__main__':
    def main():
        class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
        type_and_var_list = Holder.extract_var_declaration(class_transmit_code)
        # такой будет вывод, когда подключим все массивы и функции
        if False:
            for elem in type_and_var_list:
                print(V8ArraysWrapper.make_getter_and_setter_add(*elem))

            for elem in type_and_var_list:
                print(V8ScalarWrappers.make_scalar_getter(*elem))
                print(V8ScalarWrappers.make_scalar_setter(*elem))
        else:
            array_wrapper = V8ArraysWrapper(0, 0)
            # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
            # scalars and accessors in blueprint
            print(V8ArraysWrapper.make_scalars_and_accessors_with_formating(type_and_var_list))
            # arrays
            for elem in type_and_var_list:
                print(V8ArraysWrapper.make_array_index_getter(*elem))
                print(V8ArraysWrapper.make_array_index_setter(*elem))
                print(array_wrapper.make_array_getter(*elem))

    main()


