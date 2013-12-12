# coding: utf-8
__author__ = 'Igor'

# App
import app_utils
from _v8_api import scalars

# Последняя точка
LAST_LEVEL_GETTER_ = "LastLevelGetterByIdx_"
LAST_LEVEL_SETTER_ = "LastLevelSetterByIdx_"

# По обращению к массиву без []
ZERO_LEVEL_GETTER_ = "zero_level_getter_"


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
        return LAST_LEVEL_GETTER_ + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + \
               '(\n      uint32_t index, \n      const v8::PropertyCallbackInfo<v8::Value>& info)'

    @is_array
    def do_last_level_getter_by_idx(self):
        return 'void V8' + self.class_name_ + '::' \
               + self.make_last_level_getter_declaration() \
               + '\n  {\n' + \
               '  if (index < ' \
               + self.util_.build_accessor_name_by_array_name(self.var_name_)[1] + ') {\n' + \
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
               + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + '(\n' + \
               '  uint32_t index,\n' + \
               '  Local<Value> value,\n' + \
               '    const PropertyCallbackInfo<Value>& info) {\n' + \
               '}\n'

    @is_array
    def do_zero_level_getter(self):
        return 'static void ' + ZERO_LEVEL_GETTER_ \
               + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + '(\n' + \
               '      Local<String> name,\n' + \
               '      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
               '  Local<Object> self = info.Holder();\n' + \
               '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
               '  void* ptr = wrap->Value();\n' + \
               '  ' + self.class_name_ + '* database = static_cast<SmallBase*>(ptr);\n' + \
               '  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(\n' + \
               '      Isolate::GetCurrent(),\n' + \
               '      var_array_blueprint_);\n' + \
               '  Handle<Object> instance = templ->NewInstance();\n' + \
               '  Handle<External> array_handle = External::New(database->' \
               + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + ');\n' + \
               '  instance->SetInternalField(0, array_handle);\n' + \
               '  info.GetReturnValue().Set<v8::Object>(instance);\n' + \
               '}\n'

    @is_array
    def connect_getters_and_setters(self):
        # Затираем, если что-то было по скалярам
        return '  result->SetAccessor(String::New(\"' + \
               self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + "\"), " + ZERO_LEVEL_GETTER_ + \
               self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + ');\n' + \
               '  result->SetIndexedPropertyHandler(' \
               + LAST_LEVEL_GETTER_ + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + ',' \
               + LAST_LEVEL_SETTER_ + self.util_.build_accessor_name_by_array_name(self.var_name_)[0] + ");"


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

    def make_resets_persistent_array_handles(self):
        pass
