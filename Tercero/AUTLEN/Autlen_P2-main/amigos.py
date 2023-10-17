import numbers
import ast

class ASTMagicNumberDetector(ast.NodeVisitor):
    def __init__(self):
        self.magic_numbers = 0

    def _check_magic_number(self, number: complex) -> None:
        if isinstance(number, numbers.Number) and number != 0 and number != 1 and number != (1j):
            return True

    def visit_Num(self, node: ast.Num) -> None:
        if self._check_magic_number(node.n):
            self.magic_numbers += 1

    # Para Python >= 3.8
    def visit_Constant(self, node: ast.Constant) -> None:
        if self._check_magic_number(node.value):
            self.magic_numbers += 1


class ASTDotVisitor(ast.NodeVisitor):
    def __init__(self) -> None:
        self.level = 0
        self.n_node = 0
        self.last_parent: Optional[int] = None
        self.last_field_name = ""

    def generic_visit(self, node: ast.AST) -> None:
        if self.n_node == 0:
            print('digraph {')

        #self.last_parent = self.n_node

        print(f's{self.n_node}:[label="{type(node)}"]')

        if self.last_parent != None:
            print(f's{self.last_parent} -> s{self.n_node}[label={field}]')

        self.n_node += 1
        print(type(node))
        for field, value in ast.iter_fields(node): # Itera por los hijos

            print(field, ' ,..., ', value, ' ,..., ', type(value))
            print('\n\n')

            if isinstance(value, list):
                for item in value:
                    if isinstance(item, ast.AST):
                        self.visit(item)
            elif isinstance(value, ast.AST):
                self.level += 1
                print('level: ', self.level)

                self.visit(value)

# usar un esquema similar al generic_visit de la clase padre para recorrer los hijos del nodo actual
# obtener los nodos hijos (nodos AST y listas de nodos AST) del nodo actual
# obtener los campos hijos (el resto) del nodo actual
# procesar todos los campos hijos obtenidos del nodo actual (imprimir sus valores)
# procesar todos los nodos hijos obtenidos del nodo actual (llamada a visit)