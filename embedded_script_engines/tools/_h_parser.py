# coding: utf-8

# std
import re

# App
from _utils import remove_cc_comments, delete_double_spaces

class VarDeclaration(object):
    class Type(object):
        def __init__(self, type_name):
            self.name = type_name

    def __init__(self, type_name, name):
        self.type = VarDeclaration.Type(type_name)
        self.name = name


class Holder(object):
    @staticmethod
    def first_filtration(code_lines):
        """ Возвращает строку, в которой содержится все пары тип + имя переменной

        class {
            // Work
            Type var;
            Type function(Type var);
            Type var[SOME];

            Type function(
                Type0 var);

            // Don't work
            Type<Type<
                Var> var;
            Type function(
                Type1 var,
                Type0 var);

            // May be not work
            Type function() {

            }
        }
        """
        result = []
        filter_regex = "bool""|int""|vector<""|string""|char"

        for line in code_lines:
            # Фильтрация кода
            # Может негенерить много ошибок
            # Можно внутри класса разбить так.
            # Сперва вытянуть в строку.
            # Затем разбить ;/:/ и только потом отфильтровать.
            if '(' not in line \
                    and ")" not in line \
                    and ";" in line \
                    and "{" not in line \
                    and "}" not in line \
                    and "#" not in line \
                    and "public:" not in line \
                    and "private" not in line \
                    and "protected" not in line \
                    and "using" not in line:
                pattern = re.compile(filter_regex)
                search_result = pattern.search(line)
                if search_result:
                    line_copy = line
                    line_copy = line_copy.lstrip().rstrip()
                    line_copy = remove_cc_comments(line_copy)
                    line_copy = delete_double_spaces(line_copy)
                    result.append(line_copy)

        return '\n'.join(result)

    @staticmethod
    def extract_var_declaration(source):
        code_lines = source.split('\n')
        declaration_string = Holder.first_filtration(code_lines)

        # Похоже вся магия здесь
        folded_string = Holder.end_filtration(declaration_string)

        # Похоже на итоговую запаковку
        type_name_list = Holder.make_type_value_list(folded_string)
        return type_name_list

    @staticmethod
    def remove_lr_spaces(string):
        return string.rstrip().lstrip()

    @staticmethod
    def make_type_value_list(folded_string):
        folded_string = Holder.remove_lr_spaces(folded_string)
        declarations = folded_string.split(' ')

        result = []
        var_type = ""
        # Bug was here
        for index, record in enumerate(declarations):
            record = Holder.remove_lr_spaces(record)  # Да, эти лучше тоже отфильтровать
            if record:
                if index % 2:
                    var_name = record
                    if var_type and var_name:
                        result.append((var_type, var_name))
                else:
                    var_type = record
                    # Bug was here
        return result

    @staticmethod
    def end_filtration(declaration_string):
        declaration_string = declaration_string\
            .replace('\t', " ") \
            .replace(';', "") \
            .replace('\n\t', " ") \
            .replace("  ", " ") \
            .replace('\n', " ")
        declaration_string = delete_double_spaces(declaration_string)
        return declaration_string

