# coding: utf-8

# App
from generators_cpp_code.v8_api_gen import vectors
from generators_cpp_code.v8_api_gen import scalars
from parsers_cpp_code import header_parser


class BuilderArrayWrapper(object):
    def __init__(self, type_and_var_list, source):
        self.type_and_var_list_ = type_and_var_list
        self.class_name_ = self.type_and_var_list_[0][2]
        self.source_ = source

    # ::Blueprint()
    @staticmethod
    def __do_blueprint_method_decl():
        return 'CreateOwnBlueprint(\n' + \
               '      v8::Isolate* isolate)'

    def blueprint_method_decl(self):
        return '  static v8::Handle<v8::ObjectTemplate> ' + self.__do_blueprint_method_decl() + ';'

    def blueprint_method_impl(self):
        # ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
        # еще добавил формирование функции CreateBlueprint
        result = 'v8::Handle<v8::ObjectTemplate> V8' + self.class_name_ + '::CreateOwnBlueprint(\n' + \
                 '      v8::Isolate* isolate) \n  {\n'

        result += '  HandleScope handle_scope(isolate);\n' \
                  + '\n  Handle<ObjectTemplate> result = ObjectTemplate::New();\n' \
                  + '  result->SetInternalFieldCount(1);\n'

        for elem in self.type_and_var_list_:
            connect = vectors.V8ArraysWrapper(*elem).connect_getters_and_setters()
            if connect:
                result += connect
                result += '\n'

        # Нужно правильно выйти
        result += '\n  return handle_scope.Close(result);\n'
        result += '}'

        return result

    # ::New()
    def __do_new_method_decl(self):
        return 'New(' + self.class_name_ + '* database, v8::Isolate *isolate)'

    def new_method_decl(self):
        return '  static v8::Handle<v8::Object> ' + self.__do_new_method_decl() + ';'

    def new_method_impl(self):
        return 'Handle<Object> V8' + self.class_name_ + '::' + self.__do_new_method_decl() + ' {\n' + \
               '  HandleScope handle_scope(isolate);\n' + \
               '  Context::Scope scope(isolate->GetCurrentContext());\n' + \
               '\n' + \
               '  Handle<ObjectTemplate> raw_template = \n' + \
               '      CreateOwnBlueprint(isolate);    \n' + \
               '\n' + \
               '  Handle<ObjectTemplate> templ =\n' + \
               '      Local<ObjectTemplate>::New(isolate, raw_template);\n' + \
               '\n' + \
               '  Handle<Object> result = templ->NewInstance();\n' + \
               '  Handle<External> map_ptr = External::New(database);\n' + \
               '\n' + \
               '  result->SetInternalField(0, map_ptr);\n' + \
               '  return handle_scope.Close(result);\n' + \
               '}\n'

    # ::Arrays1D
    def zero_level_getters_impl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            code = array_wrapper.do_zero_level_getter()
            if code:
                yield code

    def zero_level_getters_decl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            name = array_wrapper.make_zero_level_getter_declaration()
            if name:
                yield '  static void ' + name + ';\n'

    def last_level_getters_impl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            getter = array_wrapper.do_last_level_getter_by_idx()
            if getter:
                yield getter

    def last_level_getters_decl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            getter_declaration = array_wrapper.make_last_level_getter_declaration()
            if getter_declaration:
                yield '  static void ' + getter_declaration + ';\n'

    def last_level_setters_impl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            setter = array_wrapper.do_last_level_setter_by_idx()
            if setter:
                yield setter

    def last_level_setters_decl(self):
        for elem in self.type_and_var_list_:
            array_wrapper = vectors.V8ArraysWrapper(*elem)
            setter_declaration = array_wrapper.make_last_level_setter_declaration()
            if setter_declaration:
                yield '  static void ' + setter_declaration + ';\n'

    # ::Scalars
    def scalar_getters_decl(self):
        dec_wrappers = header_parser.extract_variable_declaration_own(
            self.source_, self.class_name_)

        code = scalars.do_scalar_getters_decl(dec_wrappers)
        return code

    def scalar_setters_decl(self):
        dec_wrappers = header_parser.extract_variable_declaration_own(
            self.source_, self.class_name_)

        code = scalars.do_scalar_setter_decl(dec_wrappers)
        return code

    def scalar_getters_impl(self):
        dec_wrappers = header_parser.extract_variable_declaration_own(
            self.source_, self.class_name_)

        code = scalars.do_scalar_getter_impl(dec_wrappers, self.class_name_)
        return code

    def scalar_setters_impl(self):
        dec_wrappers = header_parser.extract_variable_declaration_own(
            self.source_, self.class_name_)

        code = scalars.do_scalar_setter_impl(dec_wrappers, self.class_name_)
        return code



