# coding: utf-8
import random
import unittest

# Unit
from parsers_cpp_code import header_parser

# Заголовок таки должен компилироваться,
#   поэтому откровенного бреда там быть не должно
SIMPLE_CLASS = """
class Foo {\n
private:\n
\n
public:\n
    int  i;\n
    int get(
        int k,
        int j);
    int array[10];\n
    int array[10][10];
    Point array[9];\n
};\n
"""


class TestHeaderParser(unittest.TestCase):
    def test_shuffle(self):
        extractor = header_parser.HeaderParserHandmade()
        declarations = extractor.extract_var_declaration(SIMPLE_CLASS)
        print declarations


