from parsers_cpp_code import header_parser

def get_declarations_from_header(source_code):
    type_and_var_list = header_parser.Holder.extract_var_declaration(source_code)
    result = []
    class_name = "DataBase"

    for record in type_and_var_list:
        updated = list(record)
        updated.append(class_name)
        type_var = updated[0]
        bad = 'vector' in updated[0] or \
              'string' in updated[0] or \
              'static' in updated[0] or \
              '=' in updated[0] or \
              '*' in type_var
        if not bad:
            result.append(updated)
    return result, class_name


def make_header_file(header_name, class_name, builder, header_to_wrap):
    header_name_tmp = header_name+'.h'
    directive = header_name_tmp.replace('/', '_').replace('.', '_').upper() + '_'

    # header
    header_code = []
    header_code.append('#ifndef ' + directive)
    header_code.append('#define ' + directive)
    header_code.append('')
    header_code.append('// Other')
    header_code.append('#include <v8.h>')
    header_code.append('')
    header_code.append('#include "'+header_to_wrap+'"')
    header_code.append('class V8' + class_name + ' {')
    header_code.append(' public:')
    header_code.append(builder.make_blueprint_header())
    header_code.append('')
    header_code.append(builder.make_new_header())
    header_code.append('')
    header_code.append('  //$ZeroLevelGetters')
    for impl in builder.get_zero_level_getters_header():
        header_code.append(impl)

    header_code.append('  //$LastLevelSetters')
    for impl in builder.get_last_level_setters_header():
        header_code.append(impl)

    header_code.append('  //$LastLevelAccessors')
    for impl in builder.get_last_level_getters_header():
        header_code.append(impl)

    # Static
    header_code.append('};')
    header_code.append('#endif  // ' + directive)
    return header_code


def make_source_file(builder):
    source_code = []
    source_code.append('#include "arrays.h"')
    source_code.append('#include "process.h"')
    source_code.append('')
    source_code.append('using v8::String;')
    source_code.append('using v8::ObjectTemplate;')
    source_code.append('using v8::Object;')
    source_code.append('using v8::HandleScope;')
    source_code.append('using v8::Handle;')
    source_code.append('using v8::Local;')
    source_code.append('using v8::Value;')
    source_code.append('using v8::External;')
    source_code.append('using v8::Isolate;')
    source_code.append('using v8::Number;')
    source_code.append('using v8::Undefined;')

    source_code.append('')
    source_code.append(builder.make_blueprint())
    source_code.append('')
    source_code.append(builder.make_new_method())

    source_code.append('//$LastLevelGetters')
    for impl in builder.get_last_level_getters_src():
        source_code.append(impl)

    source_code.append('//$LastLevelSetters')
    for impl in builder.get_last_level_setters_src():
        source_code.append(impl)

    source_code.append('//$ZeroLevelGetters')
    for impl in builder.get_zero_level_getters_src():
        source_code.append(impl)

    return source_code