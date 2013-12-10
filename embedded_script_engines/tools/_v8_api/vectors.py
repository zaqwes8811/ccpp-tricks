# coding: utf-8
__author__ = 'Igor'

# App
import app_utils
from _v8_api import scalars

# Последняя точка
LAST_LEVEL_GETTER_ = "last_level_getter_by_idx_"
LAST_LEVEL_SETTER_ = "last_level_setter_by_idx_"

# По обращению к массиву без []
ZERO_LEVEL_GETTER_ = "zero_level_getter_"


class V8ArraysWrapper(object):
    """
    Constraints:
        Работает только с int array[]

        Не рабоатет с:
            any array[][];
            any array[];
    """
    def __init__(self, var_type, var_name):
        self.var_type_ = var_name
        self.util_ = app_utils.Util()

    @staticmethod
    def do_last_level_getter_by_idx(var_type, var_name):
        result = ""
        if V8ArraysWrapper.is_array_name(var_name):
            result = 'static void '+LAST_LEVEL_GETTER_ \
                     + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + \
                     '(\n      uint32_t index, \n      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
                     '  if (index < ' \
                     + app_utils.Util.build_accessor_name_by_array_name(var_name)[1] + ') {\n' + \
                     '    v8::Local<v8::Object> self = info.Holder();\n' + \
                     '    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
                     '    void* ptr = wrap->Value();\n' + \
                     '    int* array = static_cast<int*>(ptr);\n' + \
                     '    info.GetReturnValue().Set(v8::Number::New(array[index])' + ');\n' + \
                     '  } else {\n' + \
                     '    info.GetReturnValue().Set(Undefined());\n' + \
                     '  }\n' + \
                     '}\n'
        return result

    @staticmethod
    def is_array_name(var_name_local):
        return "[" in var_name_local

    @staticmethod
    def do_last_level_setter_by_idx_NI(var_type, var_name):
        result = ""
        if V8ArraysWrapper.is_array_name(var_name):
            # .lower()
            result = 'static void '+LAST_LEVEL_GETTER_ \
                     + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + '(\n' + \
                     '  uint32_t index,\n' + \
                     '  Local<Value> value,\n' + \
                     '    const PropertyCallbackInfo<Value>& info) {\n' + \
                     '}\n'
        return result

    def do_zero_level_getter(self, var_type, var_name):
        """
        About: Setter не нужен в нашем случае
        """
        result = ""
        if V8ArraysWrapper.is_array_name(var_name):
            result = 'static void ' + ZERO_LEVEL_GETTER_ \
                     + self.util_.build_accessor_name_by_array_name(var_name)[0] + '(\n' + \
                     '      Local<String> name,\n' + \
                     '      const PropertyCallbackInfo<Value>& info) \n  {\n' + \
                     '  Local<Object> self = info.Holder();\n' + \
                     '  Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));\n' + \
                     '  void* ptr = wrap->Value();\n' + \
                     '  SmallBase* database = static_cast<SmallBase*>(ptr);\n' + \
                     '  Handle<ObjectTemplate> templ = Local<ObjectTemplate>::New(\n' + \
                     '      Isolate::GetCurrent(),\n' + \
                     '      var_array_blueprint_);\n' + \
                     '  Handle<Object> instance = templ->NewInstance();\n' + \
                     '  Handle<External> array_handle = External::New(database->' \
                     + self.util_.build_accessor_name_by_array_name(var_name)[0] + ');\n' + \
                     '  instance->SetInternalField(0, array_handle);\n' + \
                     '  info.GetReturnValue().Set<v8::Object>(instance);\n' + \
                     '}\n'
        return result


    @staticmethod
    def connect_getters_and_setters(var_type, var_name):
        # for scalars
        result = "  result->SetAccessor(String::New(\"" + var_name + "\"), v8_get_" \
                 + var_name + ", v8_set_" + var_name + ");"
        result = app_utils.Util.is_array(result, var_name, var_type, "add")

        # for arrays
        if V8ArraysWrapper.is_array_name(var_name):
            # Затираем, если что-то было по скалярам
            result = "\n" + \
                     '  result->SetAccessor(String::New(\"' + \
                     app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + "\"), " + ZERO_LEVEL_GETTER_ + \
                     app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + ');\n' + \
                     '  result->SetIndexedPropertyHandler(' \
                     + LAST_LEVEL_GETTER_ + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + ',' \
                     + LAST_LEVEL_SETTER_ + app_utils.Util.build_accessor_name_by_array_name(var_name)[0] + ");"
        return result

    @staticmethod
    def make_scalars_and_accessors_with_formating(type_and_var_list):
        # ВРЕМЕННЫЙ вывод, пока не зарегистрировали массивы!) очищенный от лишних пробелов и отформатированный!
        # еще добавил формирование функции CreateBlueprint
        result = 'v8::Handle<v8::ObjectTemplate> CreateBlueprint(\n' + \
                 '      v8::Isolate* isolate) {\n'

        for elem in type_and_var_list:
            result += V8ArraysWrapper.connect_getters_and_setters(*elem) + "\n"

        result += '\n}'

        result = result.replace('\n\n', '\n')

        # Все ж стирается!?
        for elem in type_and_var_list:
            result = result + scalars.V8ScalarWrappers.make_scalar_getter(*elem) \
                     + scalars.V8ScalarWrappers.make_scalar_setter(*elem)

        result = result.replace('\n ', '\n')
        result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
        result = result.replace("}\n", "}\n\n").replace("\n\n\n", "\n\n")

        return result
