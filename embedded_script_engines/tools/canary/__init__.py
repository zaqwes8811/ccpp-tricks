# coding: utf-8
# Other
from generator.cpp import utils
from generator.cpp import ast

from parsers_cpp_code import header_ast_parser

# Main()
filename = 'idata/up2D.h'
source = utils.ReadFile(filename, 'r')

# Можно выделить все кроме 2D-массивов
print header_ast_parser.ASTHeaderParser(source, filename).extract_declarations()
