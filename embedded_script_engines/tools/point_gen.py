# coding: utf-8
import re  # регулярные выражения

# std
import sys

# Third_party
from generator.cpp import utils

# App
from _units import extract_variable_declaration
from _units import make_wrapper_class


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
            impls.append((i, elem.get_wrapper_class_name()))
        else:
            print d



    #for impl in impls:
    #    print impl

    _code = make_wrapper_class(impls)
    for line in _code:
        print line

    f = open('forge_v8_point.h', 'w')
    #for line in _code:
    f.write(('\r\n'.join(_code))
        #.replace('\n\r\n', '\n')
        .replace('\r', '@')
        .replace('@', ''))

    #print(elem.make_scalar_setter())
    #elif Dart


if __name__ == '__main__':
    main()


