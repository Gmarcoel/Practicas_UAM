import ast, numbers, inspect, types

class ASTMagicNumberDetector(ast.NodeVisitor):
    def __init__(self):
        self.magic_numbers = 0        
    def _check_magic_number(self, number: complex) -> None:
        if number.imag == 0 and number.real > 0:
            if isinstance(number, numbers.Number):
                return True

    def visit_Num(self, node: ast.Num) -> None:
        if self._check_magic_number(node.n):
            self.magic_numbers+=1
        
    def visit_Constant(self, node: ast.Constant) -> None:
        if self._check_magic_number(node.value):
            self.magic_numbers += 1
"""
Usando la misma clase NodeVisitor, cread una subclase
“ASTDotVisitor” en el mismo módulo que imprima el AST en el formato dot de
Graphviz (os será útil para visualizar los ejercicios siguientes). Por ejemplo, para la
siguiente función:
"""
class ASTDotVisitor(ast.NodeVisitor):
    def __init__(self) -> None:
        self.level = 0
        self.n_node = 0
        self.last_parent: Optional[int] = None
        self.last_field_name = ""

    def generic_visit(self, node: ast.AST) -> None:
        
        if self.level == 0:
            print('digraph {')

        self.n_node += 1
        
        
        
        
        traza = "s" + str(self.n_node) + "[label=\"" + type(node).__name__ 
        push = ""
        #print("PADRASTRO", self.last_parent)
        if self.last_parent:
           # push = "s" + str(self.last_parent) + "->s" + str(self.n_node) + "[label=\"" + str(self.last_field_name) + "\"]"
           push = "s" + str(self.last_parent) + "->s" + str(self.n_node) + "[label=\"" + str(self.last_field_name) + "\"]"


        self.level += 1
        
        
        # Bucle por todos los nodos hijos
        fs = ""
        el_papa = self.n_node
        for field, value in ast.iter_fields(node):
            
            
            #print("PADRE: ", self.last_parent)
            #print("FIELD: ", field)
            #print("-----------------------------------------------------")

            
            if isinstance(value, list):
                for item in value:
                    if isinstance(item, ast.AST):
                        # print("ELTIPO" + str(type(item)))
                        self.last_parent = el_papa
                        #print("PADRE1: ", self.last_parent)
                        self.last_field_name = field
                        self.visit(item)
                        # if isinstance(item, ast.AST):
                        #     self.visit(item) 
                    
            elif isinstance(value, ast.AST):
                self.last_field_name = field
                self.last_parent = el_papa
                #print("PADRE2: ", value.last_parent)
                self.visit(value)
            
            else:
                #print("PADRINO: ", self.last_parent)
                if fs != "":
                    fs += ","
                fs = fs + " " + str(field) + "=" + str(value)
        # print("s"  + str(self.n_node) + "[label=\"" + type(node).__name__  + "(" + fs + ")\"]")
        print(traza + "(" + str(fs) +")\"]")
        if push:
            print(push)
        self.level -= 1
        if self.level == 0:
            print('}')



"""
Usando la clase NodeTransformer, cread una subclase
“ASTReplaceNum” que reciba como argumento un número y reemplace todos los
números del código por dicho número. Comprueba el funcionamiento mediante la
función “transform_code” que se proporciona:
"""
class ASTReplaceNum(ast.NodeTransformer):
    def __init__(self, number: complex) -> None:
        self.number = number
    def visit_Num(self, node: ast.Num) -> ast.AST:
        return ast.Num(self.number)

"""
Esta función recibe una función de Python y un NodeTransformer y devuelve una
nueva función usando el AST modificado.
La diferencia entre NodeTransformer y NodeVisitor es que NodeTransformer espera
que los métodos implementados devuelvan un nodo que reemplace al nodo visitado.
En caso de que no queramos reemplazar el nodo visitado bastará con devolver el
propio nodo. Por tanto, el método “visit” modificará el AST original y retornará dicho
AST modificado.
El código siguiente ilustra el uso de esta clase:
"""
def transform_code(f, transformer):
    f_ast = ast.parse(inspect.getsource(f))
    new_tree = ast.fix_missing_locations(transformer.visit(f_ast))
    old_code = f.__code__
    code = compile(new_tree, old_code.co_filename, 'exec')
    new_f = types.FunctionType(code.co_consts[0], f.__globals__)
    return new_f



"""
Parte d
-----------------------
Finalmente simularemos la realización de un posible paso de
optimización de un compilador. Para ello se debe programar una subclase
“ASTRemoveConstantIf” de NodeTransformer que reemplace aquellos “if” del código
cuya expresión a evaluar sea literalmente “True” o “False” por la parte del nodo “If”
correspondiente. En un compilador real este paso podría ser una eliminación de
ramas muertas después de simplificar la expresión de los if.
class ASTRemoveConstantIf(ast.NodeTransformer):
    # reemplace aquellos “if” del código
    # cuya expresión a evaluar sea literalmente “True” o “False” por la parte del nodo “If”
    # correspondiente. En un compilador real este paso podría ser una eliminación de
    return
    
"""
class ASTRemoveConstantIf(ast.NodeTransformer):
    def visit_If(self, node: ast.If) -> ast.AST:
        self.generic_visit(node)
        if isinstance(node.test, ast.NameConstant):
            if node.test.value:
                return node.body
            else:
                return node.orelse
        else:
            return node