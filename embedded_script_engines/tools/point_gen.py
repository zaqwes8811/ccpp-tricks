# coding: utf-8
import re  # регулярные выражения

# std
import sys

# Third_party
from generator.cpp import utils

# App
from _units import extract_variable_declaration
from _units import make_header
from _units import make_source


def main():
    header_file_name = 'test-data/point.h'
    source = utils.ReadFile(header_file_name)

    # zaqwes
    vars = extract_variable_declaration(source, header_file_name)

    #if
    # Make V8 view
    impls = []
    declarations = []
    for elem in vars:
        i, d = elem.make_scalar_getter()
        if d:
            impls.append((i, elem.get_wrapper_class_name()))
            declarations.append((d, elem.get_wrapper_class_name()))
        else:
            print i



    _code = make_header(declarations)
    f = open('forge_v8_point.h', 'w')
    f.write(('\r\n'.join(_code))
        .replace('\r', '@')
        .replace('@', ''))
    f.close()

    _code = make_source(impls)
    for line in _code:
        print line



if __name__ == '__main__':
    main()


