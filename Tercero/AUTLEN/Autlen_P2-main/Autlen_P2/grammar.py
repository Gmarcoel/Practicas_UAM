from __future__ import annotations

from collections import deque
from typing import AbstractSet, Collection, MutableSet, Optional


class RepeatedCellError(Exception):
    """Exception for repeated cells in LL(1) tables."""


class SyntaxError(Exception):
    """Exception for parsing errors."""


class Production:
    """
    Class representing a production rule.

    Args:
        left: Left side of the production rule. It must be a character
            corresponding with a non terminal symbol.
        right: Right side of the production rule. It must be a string
            that will result from expanding ``left``.

    """

    def __init__(self, left: str, right: str) -> None:
        self.left = left
        self.right = right

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented
        return (
            self.left == other.left
            and self.right == other.right
        )

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}({self.left!r} -> {self.right!r})"
        )

    def __hash__(self) -> int:
        return hash((self.left, self.right))


class Grammar:
    already_checked_non_terminals = set()
    pr = 0
    """
    Class that represent a grammar.

    Args:
        terminals: Terminal symbols of the grammar.
        non_terminals: Non terminal symbols of the grammar.
        productions: Production rules of the grammar.
        axiom: Axiom of the grammar.

    """

    def __init__(
        self,
        terminals: AbstractSet[str],
        non_terminals: AbstractSet[str],
        productions: Collection[Production],
        axiom: str,
    ) -> None:
        if terminals & non_terminals:
            raise ValueError(
                "Intersection between terminals and non terminals "
                "must be empty.",
            )

        if axiom not in non_terminals:
            raise ValueError(
                "Axiom must be included in the set of non terminals.",
            )

        for p in productions:
            if p.left not in non_terminals:
                raise ValueError(
                    f"{p}: "
                    f"Left symbol {p.left} is not included in the set "
                    f"of non terminals.",
                )
            if p.right is not None:
                for s in p.right:
                    if (
                        s not in non_terminals
                        and s not in terminals
                    ):
                        raise ValueError(
                            f"{p}: "
                            f"Invalid symbol {s}.",
                        )

        self.terminals = terminals
        self.non_terminals = non_terminals
        self.productions = productions
        self.axiom = axiom

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}("
            f"terminals={self.terminals!r}, "
            f"non_terminals={self.non_terminals!r}, "
            f"axiom={self.axiom!r}, "
            f"productions={self.productions!r})"
        )

    def compute_first(self, sentence: str) -> AbstractSet[str]:
        """
        Method to compute the first set of a string.

        Args:
            str: string whose first set is to be computed.

        Returns:
            First set of str.
        """
        first = set()
        for s in sentence:
            if s in self.terminals:
                if s != '':
                    first.add(s)
                    break
            elif s in self.non_terminals:
                for p in self.productions:
                    if p.left == s:
                        if p.right == '':
                            first |= self.compute_first(sentence[1:])
                        else:
                            first |= self.compute_first(p.right)
                break
            else:
                raise ValueError(
                    f"Invalid symbol {s}.",
                )
        # if '' in first:
        #     first.remove('')     
        if len(first)==0:
            first.add('')
            
        return first
        

    """
        primeros=set()
        if sentence[0] in self.terminals:
            primeros.add(sentence[0])
        elif sentence[0] in self.non_terminals:
                
        for element in sentence:
            if element in self.terminals:
    """

    def compute_follow(self, symbol: str) -> AbstractSet[str]:
        """
        Method to compute the follow set of a non-terminal symbol.

        Args:
            symbol: non-terminal whose follow set is to be computed.

        Returns:
            Follow set of symbol.
        """
        self.pr+=1

        follow = set()
        if symbol in self.already_checked_non_terminals:
            self.pr=self.pr-1
            return set()
        else:
            self.already_checked_non_terminals.add(symbol)

        if symbol==self.axiom:
            follow.add('$')
            
        for p in self.productions:
            pos=p.right.find(symbol)
            while pos!=-1:
                if pos==len(p.right)-1:
                    if symbol == p.left:
                        follow |= self.compute_first(p.left)
                    else:
                        follow |= self.compute_follow(p.left)
                elif p.right[pos+1] in self.non_terminals:
                    follow |= self.compute_first(p.right[pos+1:])
                    if '' in self.compute_first(p.right[pos+1:]):
                        follow.remove('')
                        follow |= self.compute_follow(p.left)
                elif p.right[pos+1] in self.terminals:
                    follow.add(p.right[pos+1])
                pos=p.right[pos+1:].find(symbol)
        
        self.pr=self.pr-1
        if self.pr==0:
            self.already_checked_non_terminals = set()

        
        return follow




            
        

	

    def get_ll1_table(self) -> Optional[LL1Table]:
        """
        Method to compute the LL(1) table.

        Returns:
            LL(1) table for the grammar, or None if the grammar is not LL(1).
        """
        
        # Create the LL(1) table
        cells = []
        terminals = self.terminals | {'$'}
        
        t = LL1Table(self.non_terminals, terminals, []) 
        for p in self.productions: 
            for s in self.compute_first(p.right): 
                 
                if s != '': 
                    try: 
                        
                        t.add_cell(TableCell(p.left, s, p.right) ) 
                    except RepeatedCellError:
                        return None 
                else:
                    for n in self.compute_follow(p.left): 
                        if n != '': 
                            try: 
                                t.add_cell(TableCell(p.left, n, p.right)) 
                            except RepeatedCellError: 
                                return None 
        return t 
         
                    

     
        
        
        
        
        
        #return LL1Table(non_terminals=self.non_terminals, terminals=self.terminals, cells)
        
        
        

	# TO-DO: Complete this method for exercise 5...

    def is_ll1(self) -> bool:
        return self.get_ll1_table() is not None

class TableCell:
    """
    Cell of a LL1 table.

    Args:
        non_terminal: Non terminal symbol.
        terminal: Terminal symbol.
        right: Right part of the production rule.

    """

    def __init__(self, non_terminal: str, terminal: str, right: str) -> None:
        self.non_terminal = non_terminal
        self.terminal = terminal
        self.right = right

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented
        return (
            self.non_terminal == other.non_terminal
            and self.terminal == other.terminal
            and self.right == other.right
        )

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}({self.non_terminal!r}, {self.terminal!r}, "
            f"{self.right!r})"
        )

    def __hash__(self) -> int:
        return hash((self.non_terminal, self.terminal))

class LL1Table:
    """
    LL1 table.

    Args:
        non_terminals: Set of non terminal symbols.
        terminals: Set of terminal symbols.
        cells: Cells of the table.

    """

    def __init__(
        self,
        non_terminals: AbstractSet[str],
        terminals: AbstractSet[str],
        cells: Collection[TableCell],
    ) -> None:

        if terminals & non_terminals:
            raise ValueError(
                "Intersection between terminals and non terminals "
                "must be empty.",
            )

        for c in cells:
            if c.non_terminal not in non_terminals:
                raise ValueError(
                    f"{c}: "
                    f"{c.non_terminal} is not included in the set "
                    f"of non terminals.",
                )
            if c.terminal not in terminals:
                raise ValueError(
                    f"{c}: "
                    f"{c.terminal} is not included in the set "
                    f"of terminals.",
                )
            for s in c.right:
                if (
                    s not in non_terminals
                    and s not in terminals
                ):
                    raise ValueError(
                        f"{c}: "
                        f"Invalid symbol {s}.",
                    )

        self.terminals = terminals
        self.non_terminals = non_terminals
        self.cells = {(c.non_terminal, c.terminal): c.right for c in cells}

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}("
            f"terminals={self.terminals!r}, "
            f"non_terminals={self.non_terminals!r}, "
            f"cells={self.cells!r})"
        )

    def add_cell(self, cell: TableCell) -> None:
        """
        Adds a cell to an LL(1) table.

        Args:
            cell: table cell to be added.

        Raises:
            RepeatedCellError: if trying to add a cell already filled.
        """
        if (cell.non_terminal, cell.terminal) in self.cells:
            raise RepeatedCellError(
                f"Repeated cell ({cell.non_terminal}, {cell.terminal}).")
        else:
            self.cells[(cell.non_terminal, cell.terminal)] = cell.right

    def analyze(self, input_string: str, start: str) -> ParseTree:
        """
        Method to analyze a string using the LL(1) table.

        Args:
            input_string: string to analyze.
            start: initial symbol.

        Returns:
            ParseTree object with either the parse tree (if the elective exercise is solved)
            or an empty tree (if the elective exercise is not considered).

        Raises:
            SyntaxError: if the input string is not syntactically correct.
        """
    
    
        childs=[]
        auxchilds=[]

        pila = ["root", start]
        
	# TO-DO: Complete this method for exercise 2...
        if not input_string:
            return ParseTree(start)
        else:
            stack = ["$", start]
            tree = ParseTree(start)
            while len(stack)!=0 and len(input_string)!=0:
                top=str(stack.pop())
                top_pila=str(pila.pop())
                

                if top in self.terminals:
                    if top==input_string[0]:
                        input_string=input_string[1:]
                    else:
                        raise SyntaxError

                elif top in self.non_terminals:
                    
                    #tree = tree.children[0]    
                    
                    if (top, input_string[0]) in self.cells:
                        #for c in self.cells[(top, input_string [0])][::-1]:
                        #    childs.append(ParseTree(c))
                        #    pilita.append(c)
                        
                        for i,c in enumerate(self.cells[(top, input_string [0])][::-1]):
                            childs.append(ParseTree(c))
                            elemento = [top_pila, top]
                            pila.append(elemento)
                            

                            
                        
                            

                        auxchilds=childs
                        childs=[]
                        childs.append(ParseTree(top, auxchilds))
                        # auxchilds=childs[::-1]
                        # childs=[]
                        # childs.append(ParseTree(top, auxchilds))

                        stack+=(self.cells[(top, input_string [0])][::-1])
                        

                        
                        
                    else:
                        raise SyntaxError
                    
                    # print ((top, input_string [0]))
                    # print(self.cells.keys())
                    # if (top, input_string [0]) in self.cells:
                    #     stack+=(self.cells[(top, input_string [0])][::-1])
                    # else:
                    #     raise SyntaxError
                else:
                    raise SyntaxError
            if len(stack)!=0 or len(input_string)!=0:
                raise SyntaxError
        tree=ParseTree(start, childs)
        return tree
    


class ParseTree():
    """
    Parse Tree.

    Args:
        root: root node of the tree.
        children: list of children, which are also ParseTree objects.
    """
    def __init__(self, root: str, children: Collection[ParseTree] = []) -> None:
        self.root = root
        self.children = children

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}({self.root!r}: {self.children})"
        )

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented
        return (
            self.root == other.root
            and len(self.children) == len(other.children)
            and all([x.__eq__(y) for x, y in zip(self.children, other.children)])
        )

    def add_children(self, children: Collection[ParseTree]) -> None:
        self.children = children
