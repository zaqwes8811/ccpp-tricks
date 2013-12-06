# coding: utf-8
import re  # регулярные выражения

# Third_party
from generator.cpp import utils
from generator.cpp import ast

# App
from _units import extract_variable_declaration


def main():
    header_file_name = 'test-data/point.h'
    source = utils.ReadFile(header_file_name)
    # zaqwes
    vars = extract_variable_declaration(source, header_file_name)

    #if
    # Make V8 view
    declarations = []
    impls = []
    for elem in vars:
        d, i = elem.make_scalar_getter()
        if i:
            declarations.append(d)
            impls.append(i)
        else:
            print d

    for impl in impls:
        print impl


        #print(elem.make_scalar_setter())
    #elif Dart


if __name__ == '__main__':
    main()


