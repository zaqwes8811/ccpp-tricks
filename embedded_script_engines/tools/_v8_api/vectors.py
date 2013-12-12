# coding: utf-8
__author__ = 'Igor'

# std
import re

# App
import app_utils
from _v8_api import scalars

# Последняя точка
LAST_LEVEL_GETTER_ = "LLGetterByIdx_"
LAST_LEVEL_SETTER_ = "LLSetterByIdx_"

# По обращению к массиву без []
ZERO_LEVEL_GETTER_ = "ZLGetter_"


def is_array(method_to_decorate):
    def is_array_name(var_name_local):
        return "[" in var_name_local

    def wrapper(self):
        if is_array_name(self.var_name_):
            return method_to_decorate(self)
        else:
            return None

    return wrapper


class V8ArraysWrapper(object):
    """
    Constraints:
        Работает только с int array[]

        Не рабоатет с:
            any array[][];
            any array[];
    """

    def __init__(self, var_type, var_name):
        self.var_type_ = var_type
        self.var_name_ = var_name
        self.util_ = app_utils.Util()
        self.class_name_ = "Web"
        self.V8_GETTER_RECODER_ = {'int': 'Integer', 'std::string': 'String', 'bool': 'Boolean'}

    def make_last_level_getter_declaration(self):
        return LAST_LEVEL_GETTER_ + self.get_array_name(self.var_name_) + \
               '(\n' \
               '      uint32_t index, \n' \
               '      const v8::PropertyCallbackInfo<v8::Value>& info)'

    def make_zero_level_getter_declaration(self):
        return ZERO_LEVEL_GETTER_ \
               + self.get_array_name(self.var_name_) + '(\n' + \
               '      v8::Local<String> name,\n' + \
               '      const v8::PropertyCallbackInfo<v8::Value>& info)'

    @is_array
    def do_last_level_getter_by_idx(self):
        return 'void V8' + self.class_name_ + '::' \
               + self.make_last_level_getter_declaration() \
               + '\n  {\n' + \
               '  if (index < ' \
               + self.get_idx_threshold(self.var_name_) + ') {\n' + \
               '    v8::Local<v8::Object> self = info.Holder();\n' + \
               '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
               '    void* ptr = wrap->Value();\n' + \
               '    ' + self.var_type_ + '* array = static_cast<' + self.var_type_ + '*>(ptr);\n' + \
               '    info.GetReturnValue().Set(' + 'Number' + '::New(array[index])' + ');\n' + \
               '  } else {\n' + \
               '    info.GetReturnValue().Set(Undefined());\n' + \
               '  }\n' + \
               '}\n'

    @is_array
    def do_last_level_setter_by_idx_NI(self):
        # .lower()
        return 'static void V8' + self.class_name_ + '::' + LAST_LEVEL_GETTER_ \
               + self.get_array_name(self.var_name_) + '(\n' + \
               '  uint32_t index,\n' + \
               '  Local<Value> value,\n' + \
               '    const PropertyCallbackInfo<Value>& info) {\n' + \
               '}\n'

    #@is_array
    def do_zero_level_getter(self):
        return 'void ' + self.class_name_ + '::' + self.make_zero_level_getter_declaration() + ' \n  {\n' + \
               '  Local<Object> self = info.Holder();\n' + \
               '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
               '  void* ptr = wrap->Value();\n' + \
               '  ' + self.class_name_ + '* danger_real_ptr = static_cast<' + self.class_name_ + '*>(ptr);\n' + \
               '  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(\n' + \
               '      Isolate::GetCurrent(),\n' + \
               '      ArrayMakeBlueprint(\n' + \
               '          Isolate::GetCurrent(), \n' + \
               '          ' + LAST_LEVEL_GETTER_ + self.get_array_name(self.var_name_) + ',\n' + \
               '          ' + LAST_LEVEL_SETTER_ + self.get_array_name(self.var_name_) + "));\n" + \
               '  Handle<Object> instance = templ->NewInstance();\n' + \
               '  Handle<External> array_handle = External::New(danger_real_ptr->' \
               + self.get_array_name(self.var_name_) + ');\n' + \
               '  instance->SetInternalField(0, array_handle);\n' + \
               '  info.GetReturnValue().Set<v8::Object>(instance);\n' + \
               '}\n'

    @is_array
    def connect_getters_and_setters(self):
        # Затираем, если что-то было по скалярам
        return '  result->SetAccessor(\n      String::New(\"' + \
               self.get_array_name(self.var_name_) + "\"), \n      " + ZERO_LEVEL_GETTER_ + \
               self.get_array_name(self.var_name_) + ');'

    @staticmethod
    def get_array_name(var_name):
        result = var_name
        regular = re.compile('\[.*')
        search_result = regular.search(result)
        if search_result:
            result = result.replace(search_result.group(), "")
        return result

    @staticmethod
    def get_idx_threshold(var_name):
        result = var_name
        index = ""
        regular = re.compile('\[.*')
        search_result = regular.search(result)
        if search_result:
            index = search_result.group()
        index = index.replace("[", "").replace("]", "")
        return index


class BuilderArrayWrapper(object):
    def __init__(self, type_and_var_list):
        self.type_and_var_list_ = type_and_var_list

    #@is_array
    def make_blueprint(self):
        # ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
        # еще добавил формирование функции CreateBlueprint
        result = 'v8::Handle<v8::ObjectTemplate> CreateBlueprint(\n' + \
                 '      v8::Isolate* isolate) \n  {\n'
        for elem in self.type_and_var_list_:
            connect = V8ArraysWrapper(*elem).connect_getters_and_setters()
            if connect:
                result += connect
                result += '\n'

        # Нужно правильно выйти
        result += '\n  return handle_scope.Close(result);\n'
        result += '}'

        return result

    def get_zero_level_accessors_src(self):
        for elem in self.type_and_var_list_:
            array_wrapper = V8ArraysWrapper(*elem)
            array_wrapper.do_zero_level_getter()

    def get_zero_level_accessors_header(self):
        for elem in self.type_and_var_list_:
            array_wrapper = V8ArraysWrapper(*elem)
            yield '  static void '+array_wrapper.make_zero_level_getter_declaration()+';\n'

    """
    # arrays
    print '// Source'
    for elem in type_and_var_list:
        array_wrapper = vectors.V8ArraysWrapper(*elem)
        getter = array_wrapper.do_last_level_getter_by_idx()
        if getter:
            print getter"""

    def get_last_level_accessors_header(self):
        for elem in self.type_and_var_list_:
            array_wrapper = V8ArraysWrapper(*elem)
            getter_declaration = array_wrapper.make_last_level_getter_declaration()
            if getter_declaration:
                yield '  static void '+getter_declaration+';\n'
