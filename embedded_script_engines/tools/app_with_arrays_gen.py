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
        # такой будет вывод, когда подключим все массивы и функции
        if False:
            for elem in type_and_var_list:
                print(vectors.V8ArraysWrapper.connect_getters_and_setters(*elem))

            for elem in type_and_var_list:
                print(scalars.V8ScalarWrappers.make_scalar_getter(*elem))
                print(scalars.V8ScalarWrappers.make_scalar_setter(*elem))
        else:
            array_wrapper = vectors.V8ArraysWrapper(0, 0)
            # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
            # scalars and accessors in blueprint
            print vectors.BuilderArrayWrapper(type_and_var_list).make_blueprint()

            """
            # arrays
            print '// Source'
            for elem in type_and_var_list:
                array_wrapper = vectors.V8ArraysWrapper(*elem)
                getter = array_wrapper.do_last_level_getter_by_idx()
                if getter:
                    print getter


            print '// Header'
            for elem in type_and_var_list:
                array_wrapper = vectors.V8ArraysWrapper(*elem)
                getter_declaration = array_wrapper.make_last_level_getter_declaration()
                if getter_declaration:
                    print '  static void '+getter_declaration+';'
                    print"""

            #for
                #print(vectors.V8ArraysWrapper(None, None).do_last_level_setter_by_idx_NI(*elem))
                #print(array_wrapper.do_zero_level_getter(*elem))

    main()


