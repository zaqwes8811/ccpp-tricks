# coding: utf-8

# Other
from generator.cpp import utils

# App
from __cpp_code_parsers import header_parser
from _v8_api import vectors
import app_utils

if __name__ == '__main__':
    def main():
        class_transmit_code = utils.ReadFile('./test-data/real_test_file.h')
        type_and_var_list = header_parser.Holder.extract_var_declaration(class_transmit_code)
        expended = []
        class_name = "DataBase"
        for record in type_and_var_list:
            updated = list(record)
            updated.append(class_name)
            expended.append(updated)

        # Targets
        header_name = 'odata/arrays.h'
        directive = header_name.replace('/', '_').replace('.', '_').upper()+'_'

        # header
        header_code = []
        header_code.append('#ifndef '+directive)
        header_code.append('#define '+directive)
        header_code.append('')
        header_code.append('// Other')
        header_code.append('#include <v8.h>')
        header_code.append('')
        header_code.append('class V8'+class_name+' {')
        header_code.append(' public:')

        builder = vectors.BuilderArrayWrapper(expended)
        header_code.append('  //$ZeroLevelAccessors')
        for impl in builder.get_zero_level_accessors_header():
            header_code.append(impl)

        header_code.append('  //$LastLevelAccessors')
        for impl in builder.get_last_level_accessors_header():
            header_code.append(impl)

        # Static
        header_code.append('};')
        header_code.append('#endif  // '+directive)

        # Write
        app_utils.write_source(header_name, header_code)

        # source
        source_name = 'odata/arrays.cc'
        source_code = []
        source_code.append('#include "arrays.h"')
        source_code.append('')
        source_code.append('using v8::String;')
        source_code.append('using v8::String;')
        source_code.append('using v8::String;')
        source_code.append('using v8::String;')
        source_code.append('using v8::String;')
        source_code.append('')
        source_code.append(builder.make_blueprint())

        source_code.append('//$LastLevelAccessors')
        for impl in builder.get_last_level_accessors_src():
            source_code.append(impl)

        source_code.append('//$ZeroLevelAccessors')
        for impl in builder.get_zero_level_accessors_src():
            source_code.append(impl)

        # Write
        app_utils.write_source(source_name, source_code)

    main()


