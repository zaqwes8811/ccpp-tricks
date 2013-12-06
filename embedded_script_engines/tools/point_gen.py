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
            impls.append((i, elem.get_wrapper_class_name()))
        else:
            print d

    def make_wrapper_class(impl_local):
        code_result = []
        class_name = impl_local[0][1]
        protect_directive = class_name.upper()+'_H_'
        code_result.append('#ifndef '+protect_directive)
        code_result.append('#define '+protect_directive+'\r\n')
        code_result.append('// Other')
        code_result.append('#include <v8.h>\r\n')
        code_result.append('//@StateLess\r\nclass ' + class_name + ' {')
        code_result.append(' public:')

        # Лучше передавать указатель, но тогда это не обертка, а генератор
        code_result.append(
            '  ' + class_name + '() { }\r\n')
        code_result.append('  // TODO: It need be impl. manual')
        code_result.append('  v8::Handle<v8::Object> Forge(\r\n      '
                           'Point* point, \r\n      ' +
                           'v8::Isolate* isolate\r\n      ' +
                           'v8::Persistent<v8::ObjectTemplate>* blueprint);\r\n')
        code_result.append('  // TODO: It need be impl. manual')
        code_result.append('  v8::Handle<v8::ObjectTemplate> MakeBlueprint();\r\n')

        for impl in impl_local:
            code_result.append('  static ' + impl[0])
        code_result.append('};')
        code_result.append('#endif')
        return code_result


    #for impl in impls:
    #    print impl

    _code = make_wrapper_class(impls)
    for line in _code:
        print line


        #print(elem.make_scalar_setter())
        #elif Dart


if __name__ == '__main__':
    main()


