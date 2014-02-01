# coding: utf-8
# Other
from generator.cpp import utils

from parsers_cpp_code import header_ast_parser

# Main()
filename = 'idata/up2D.h'
source = utils.ReadFile(filename, 'r')
print source

# Можно выделить все кроме 2D-массивов
header_ast_parser.extract_variable_declaration(source, filename)
