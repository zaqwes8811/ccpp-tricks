# coding: utf-8

# std
import re


def remove_cc_comments(string):
    string_to_delete = ""
    regular = re.compile('\/\/.*')
    search_result = regular.search(string)
    if search_result:
        string_to_delete = search_result.group()
    return string.replace(string_to_delete, "")


def delete_double_spaces(string):
    return string.replace("  ", " ")

class Util(object):
    @staticmethod
    def get_fun_name_by_array_types(name):
        result = name
        index = ""
        regular = re.compile('\[.*')
        search_result = regular.search(result)
        if search_result:
            result = result.replace(search_result.group(), "")
            index = search_result.group()
        index = index.replace("[", "").replace("]", "")
        return result, index

    @staticmethod
    def is_array_(result, name, var_type, function_type):
        # 0 - нет
        # 1 - да
        # 0 - вывод без массивов!
        # 1 - вывод с массивами (по умолчанию 0)
        check_array_print = 0

        if check_array_print == 0:
            if "[" not in name and "vector" not in var_type:
                return result
            else:
                return ""
        if check_array_print == 1:
            if "[" not in name and "vector" not in var_type:
                return result
            else:
                return result
        if function_type == "add":
            return "error: bad logic (in make_getter_and_setter_add) or " \
                   + check_array_print + " != 0 or 1, default = 0"
        if function_type == "set":
            return "error: bad logic (in make_scalar_setter) or " \
                   + check_array_print + " != 0 or 1, default = 0"
        if function_type == "get":
            return "error: bad logic (in make_scalar_getter) or " \
                   + check_array_print + " != 0 or 1, default = 0"

    @staticmethod
    def clear_result(result):
        result = result.replace('\n ', '\n').replace("\n\n\n", "")
        result = result.replace('\n\n', '\n').replace('\n\n}', '\n}')
        result = result.replace("}\n", "}\n\n").replace("}\n\n}", "}\n}").replace("}\n\n\n", "}\n\n")
        return result

