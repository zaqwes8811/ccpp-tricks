

# Third_party
from generator.cpp import ast

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
                        # модификаторы и... *, & отделены от имени типа!
                        #if scalar?:
                        #elif  vector? std::vector<string>, Vector, List, Array...
                        # это не скаляр и сеттер будет другим https://developers.google.com/v8/embed
                        #else
                        #check what happened
                        #result.append(scalars.ScalarVariableField(node.name, record))
                        pass
        return result
    except KeyboardInterrupt:
        return None
    except Exception as e:
        return None
