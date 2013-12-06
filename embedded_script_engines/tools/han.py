# coding: utf-8
import re

# Other
from generator.cpp import utils

# App
from _units_han import make_array_getter, make_array_index_getter, make_scalars_and_accessors_with_formating
from _units_han import extract_var_declaration, make_getter_and_setter_add
from _units_han import make_scalar_getter, make_scalar_setter
from _units_han import make_array_index_setter


class Indicator(object):
    def __init__(self, var_type, var_name):
        self.type_ = var_type
        self.name_ = var_name

    def is_array(self):
        """
        About:
            vector vec;
            int array[]
        """
        result = False
        if '[' in self.name_ or 'vector' in self.type_:
            result = True

        return result

    def get_array_size(self):
        if self.is_array():
            return 0
        else:
            return None

if __name__ == '__main__':
    #header_file_name = '../v8/src/point.h'
    header_file_name = './test-data/han_test_.h'
    source = utils.ReadFile(header_file_name)

    type_and_var_list = extract_var_declaration(source)

    for var in type_and_var_list:
        Indicator(*var)

    # такой будет вывод, когда подключим все массивы и функции
    if False:
        for elem in type_and_var_list:
            print(make_getter_and_setter_add(*elem))

        for elem in type_and_var_list:
            print(make_scalar_getter(*elem))
            print(make_scalar_setter(*elem))
    else:
        # временный вывод, где удалены пустые строки, в которых должны быть обернуты массивы
        # scalars and accessors in blueprint
        #print type_and_var_list
        #print(make_scalars_and_accessors_with_formating(type_and_var_list))
        # arrays
        #for elem in type_and_var_list:
        #    print(make_array_index_getter(*elem))
        #    print(make_array_index_setter(*elem))
        #    print(make_array_getter(*elem))
        pass


