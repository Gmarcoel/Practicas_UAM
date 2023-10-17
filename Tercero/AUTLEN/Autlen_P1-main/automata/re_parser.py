
"""Conversion from regex to automata."""
from automata.automaton import FiniteAutomaton, State, Transition
from automata.re_parser_interfaces import AbstractREParser


class REParser(AbstractREParser):
    """Class for processing regular expressions in Kleene's syntax."""

    # _create_automaton_empty: Crea el autómata que acepta el lenguaje vacío
    def _create_automaton_empty(
        self,
    ) -> FiniteAutomaton:
        states = []
        symbols = []
        transitions = []
        q0 = State(name = "q0", is_final = True)
        states.append(q0)
        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)
        #raise NotImplementedError("This method must be implemented.")

    # _create_automaton_lambda: Crea el autómata que acepta la cadena vacía.
    def _create_automaton_lambda(
        self,
    ) -> FiniteAutomaton:
        states = []
        symbols = []
        transitions = []
        q0 = State(name = "q0", is_final = False)
        states.append(q0)
        qf = State("qf", is_final = True)
        states.append(qf)

        lambda_symbol = None
        symbols.append(lambda_symbol)

        q1qf =Transition(initial_state = q0,symbol = lambda_symbol,final_state = qf)
        transitions.append(q1qf)

        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)

    # _create_automaton_symbol: Crea el autómata que acepta un símbolo.
    def _create_automaton_symbol(
        self,
        symbol: str,
    ) -> FiniteAutomaton:
        states = []
        symbols = []
        transitions = []
        q0 = State("q0", is_final = False)
        states.append(q0)
        qf = State("qf", is_final = True)
        states.append(qf)

        symbols.append(symbol)

        q1qf =Transition(initial_state = q0,symbol = symbol,final_state = qf)
        transitions.append(q1qf)

        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)


    # _create_automaton_star: Crea el autómata para calcular la estrella de Kleene de un autómata dado
    def _create_automaton_star(
        self,
        automaton: FiniteAutomaton,
    ) -> FiniteAutomaton:
        states = list(automaton.states)
        symbols = list(automaton.symbols)
        transitions = list(automaton.transitions)
        initial_state = automaton.initial_state
        final_state = None
        #states.append(q0)

        i = 1
        for s in states:
            s.name = "q" + str(i)
            i += 1
            if s.is_final:
                s.is_final = False
                final_state = s
        
        q0 = State(name="q0", is_final=False)
        states.append(q0)
        qf = State(name="qf", is_final=True)
        states.append(qf)

        lambda_symbol = None
        if lambda_symbol not in symbols:
            symbols.append(lambda_symbol)

        transitions.append(Transition(initial_state=q0,symbol=lambda_symbol,final_state=initial_state))
        transitions.append(Transition(initial_state=q0,symbol=lambda_symbol,final_state=qf))
        transitions.append(Transition(initial_state=final_state,symbol=lambda_symbol,final_state=initial_state))
        transitions.append(Transition(initial_state=final_state,symbol=lambda_symbol,final_state=qf))


        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)


    # _create_automaton_union: Crea el autómata para calcular la unión de dos autómatas dados.
    def _create_automaton_union(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        states1 = list(automaton1.states)
        symbols1 = list(automaton1.symbols)
        transitions1 = list(automaton1.transitions)
        initial_state1 = automaton1.initial_state
        final_state1 = None

        i=1
        for s in states1:
            if s.is_final:
                s.is_final = False
                final_state1 = s

            s.name = "q" + str(i)
            i+=1


        states2 = list(automaton2.states)
        symbols2 = list(automaton2.symbols)
        transitions2 = list(automaton2.transitions)
        initial_state2 = automaton2.initial_state
        final_state2 = None

        for s in states2:
            if s.is_final:
                s.is_final = False
                final_state2 = s

            s.name = "q" + str(i)
            i+=1



        states = states1 + states2
        lambda_symbol = None
        aux = symbols1 + symbols2
        aux.append(lambda_symbol)
        symbols = []
        for i in aux:
            if i not in symbols:
                symbols.append(i)
        transitions = transitions1 + transitions2

        q0 = State(name="q0", is_final=False)
        states.append(q0)
        qf = State(name="qf", is_final=True)
        states.append(qf)
        

        transitions.append(Transition(initial_state=q0,symbol=lambda_symbol,final_state=initial_state1))
        transitions.append(Transition(initial_state=q0,symbol=lambda_symbol,final_state=initial_state2))
        transitions.append(Transition(initial_state=final_state1,symbol=lambda_symbol,final_state=qf))
        transitions.append(Transition(initial_state=final_state2,symbol=lambda_symbol,final_state=qf))



        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)


        

        



    # _create_automaton_concat: Crea el autómata para calcular la concatenación de dos autómatas dados
    def _create_automaton_concat(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        states1 = list(automaton1.states)
        symbols1 = list(automaton1.symbols)
        transitions1 = list(automaton1.transitions)
        q0 = automaton1.initial_state
        final_state1 = None

        states2 = list(automaton2.states)
        symbols2 = list(automaton2.symbols)
        transitions2 = list(automaton2.transitions)
        initial_state2 = automaton2.initial_state

        for s in states1:
            if s.is_final:
                s.is_final = False
                final_state1 = s
                break
        

        
        lambda_symbol = None
        symbols1.append(lambda_symbol)
        states = states1 + states2
        aux = symbols1 + symbols2
        symbols = []
        for i in aux:
            if i not in symbols:
                symbols.append(i)

        i=0
        for s in states:
            if s.is_final:
                s.name = "qf"
            else:
                s.name = "q" + str(i)
                i+=1

        union = Transition(initial_state = final_state1, symbol = lambda_symbol, final_state = initial_state2)
        transitions1.append(union)
        transitions = transitions1 + transitions2



        return FiniteAutomaton(initial_state=q0, states=states, symbols=symbols,transitions=transitions)
