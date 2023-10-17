
"""Evaluation of automata."""
from typing import Set

from automata.automaton import FiniteAutomaton, State
from automata.interfaces import AbstractFiniteAutomatonEvaluator


class FiniteAutomatonEvaluator(
    AbstractFiniteAutomatonEvaluator[FiniteAutomaton, State],
):
    """Evaluator of an automaton."""

    # Procesa un símbolo de la cadena (y cualquier número de 
    # transiciones   lambdas   inmediatamente   después,   mediante   la   llamada   a
    # _complete_lambdas).
    def process_symbol(self, symbol: str) -> None:
        
        aux = set()
        
        s = symbol
        if s not in self.automaton.symbols:
            raise ValueError("The symbol " + s + " is not in the dictionary.")
        else:
            for transition in self.automaton.transitions:
                for state in self.current_states: 
                    if(transition.symbol==s and transition.initial_state==state):
                        aux.add(transition.final_state)
                        #self.current_states.add(transition.final_state)

        

        self.current_states = aux
        self._complete_lambdas(self.current_states)
        
        

        """
        aux = list(self.current_states)
        l = len(aux)
        
        s = symbol
        if s not in self.automaton.symbols:
            raise ValueError("The symbol " + s + " is not in the dictionary.")
        else:
            
            i = 0
            while i < l:
                for transition in self.automaton.transitions:
                    if(transition.symbol==s and transition.initial_state==aux[i]):
                        if transition.final_state not in aux:
                            aux.append(transition.final_state)
                            l += 1
                        #self.current_states.add(transition.final_state)
                i += 1

        self.current_states = set(aux)
        self._complete_lambdas(self.current_states)
        return
        """


    # Añade al conjunto de estados pasado como argumento
    # todos los estados que sean alcanzables mediante un número arbitrario de
    # transiciones lambda
    def _complete_lambdas(self, set_to_complete: Set[State]) -> None:
        aux = list(set_to_complete)
        l = len(set_to_complete)
        i = 0
        while i < l:
            for transition in self.automaton.transitions:
                if transition.symbol == None and transition.initial_state==aux[i]:
                    set_to_complete.add(transition.final_state)
                    aux.append(transition.final_state)
                    l += 1
            i += 1

        
    # s_accepting: Indica si la cadena que se ha procesado hasta el momento se
    # acepta o no.
    def is_accepting(self) -> bool:

        for state in self.current_states:
            if state.is_final==True:
                return True

        return False    
        #raise NotImplementedError("This method must be implemented.")
