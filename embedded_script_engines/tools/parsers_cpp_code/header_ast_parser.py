# coding: utf-8

# Third_party
from generator.cpp import ast


class ArrayXD(ast.VariableDeclaration):
    pass

def extract_variable_declaration(source, header_file_name):
    """
    Abstract:
        Extract variable declaration form C++ header file.
    Args:
        source - content header file
        header_file_name - name header file

    Returns:
        [VarField0, ...]
    """
    result = []
    builder = ast.BuilderFromSource(source, header_file_name)
    try:
        for node in builder.Generate():
            if isinstance(node, ast.Class):
                for record in node.body:
                    if isinstance(record, ast.VariableDeclaration):
                        if '???' not in record.FullName():
                            #print "Not Array"
                            pass
                    if isinstance(record, ast.Function):
                        pass
                        #print record.FullName(), record.parameters
        #return result
    except KeyboardInterrupt:
        return None
    except Exception as e:
        return None

    # Добавляем массивы
    source_lines = source.split('\n')
    for line in source_lines:
        if '[' in line and '(' not in line:
            print line
