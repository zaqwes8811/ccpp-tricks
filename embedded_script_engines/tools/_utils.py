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
