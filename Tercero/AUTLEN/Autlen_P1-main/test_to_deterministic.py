"""Test evaluation of automatas."""
import unittest
from abc import ABC

from automata.automaton import FiniteAutomaton
from automata.utils import AutomataFormat, deterministic_automata_isomorphism, write_dot

import graphviz
from graphviz import Source


class TestTransform(ABC, unittest.TestCase):
    """Base class for string acceptance tests."""

    def _check_transform(
        self,
        automaton: FiniteAutomaton,
        expected: FiniteAutomaton,
    ) -> None:
        """Test that the transformed automaton is as the expected one."""
        transformed = automaton.to_deterministic()
        '''
        print(automaton)
        print()
        print(transformed)
        print()
        print(expected)
        '''
        equiv_map = deterministic_automata_isomorphism(
            expected,
            transformed,
        )

        self.assertTrue(equiv_map is not None)


    """llamar a esta funcion para obtener las imagenes de antes y despues de cada automata"""
    def generateImage(
        self,
        automaton: FiniteAutomaton,
        testname: str
    ) -> None:
        """Test that the transformed automaton is as the expected one."""
        temp = write_dot(automaton)
        s = Source(temp, filename="./images/deterministic/"+testname, format="png")
        s.view()
        
        transformed = automaton.to_deterministic()
        
        temp = write_dot(transformed)
        s = Source(temp, filename="./images/deterministic/"+testname+"_transformed", format="png")
        s.view()





    def test_case1(self) -> None:
        """Test Case 1."""
        automaton_str = """
        Automaton:
            Symbols: 01

            q0
            qf final

            --> q0
            q0 -0-> qf
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            q0
            qf final
            empty

            --> q0
            q0 -0-> qf
            q0 -1-> empty
            qf -0-> empty
            qf -1-> empty
            empty -0-> empty
            empty -1-> empty

        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)

    def test_case2(self) -> None:
        """
        Test Case 2: Comprueba que se procesan correctamente
        los autómatas que no son deterministas y poseen transiciones con lambdas.
        También prueba el correcto funcionamiento del estado empty.
        """
        automaton_str = """
        Automaton:
            Symbols: abc

            q0
            q1
            q2 
            q3
            q4
            q5
            q6
            q7
            qf final

            --> q0
            q0 --> q1
            q0 --> qf
            q1 --> q2
            q1 --> q5
            q2 -a-> q3
            q3 -b-> q4
            q4 --> q7
            q5 -c-> q6
            q6 --> q7
            q7 --> q1
            q7 --> qf
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
                Symbols: abc

                q0q1q2q5qf final
                q3
                q1q2q5q6q7qf final
                q1q2q4q5q7qf final
                empty

                --> q0q1q2q5qf
                
                q0q1q2q5qf -a-> q3
                q0q1q2q5qf -b-> empty
                q0q1q2q5qf -c-> q1q2q5q6q7qf

                q1q2q4q5q7qf -a-> q3
                q1q2q4q5q7qf -b-> empty
                q1q2q4q5q7qf -c-> q1q2q5q6q7qf

                q1q2q5q6q7qf -a-> q3
                q1q2q5q6q7qf -b-> empty
                q1q2q5q6q7qf -c-> q1q2q5q6q7qf

                q3 -a-> empty
                q3 -b-> q1q2q4q5q7qf
                q3 -c-> empty

                empty -a-> empty
                empty -b-> empty
                empty -c-> empty


        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)

    def test_case3(self) -> None:
        """
        Test Case 3: 
        Comprueba que se procesan correctamente los autómatas que no son deterministas
        con estados que unen otros estados ya unidos anteriormente con un estado
        original en común (ej el estado ab y el estado bc es unan en el estado abc y no abbc).
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1
            q2 
            q3 final

            --> q0
            q0 -a-> q0
            q0 -b-> q0
            q0 -a-> q1
            q1 -b-> q2
            q2 -a-> q3
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
                Symbols: ab

                q0 
                q0q1
                q0q2 
                q0q1q3 final

                --> q0
                
                q0 -a-> q0q1
                q0 -b-> q0
                
                q0q1 -a-> q0q1
                q0q1 -b-> q0q2

                q0q2 -a-> q0q1q3
                q0q2 -b-> q0
                
                q0q1q3 -a-> q0q1
                q0q1q3 -b-> q0q2


        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


    def test_case4(self) -> None:
        """
        Test Case 4:
        Comprueba que se procesan correctamente los autómatas que no son deterministas
        con múltiples estados finales
        """
        automaton_str = """
        Automaton:
            Symbols: 01

            q1
            q2
            q3
            q4 final

            --> q1
            q1 -0-> q1
            q1 -1-> q1
            q1 -1-> q2
            
            q2 -0-> q3
            q2 -1-> q3

            q3 -0-> q4
            q3 -1-> q4
            
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            q1
            q1q2
            q1q3
            q1q2q3
            q1q4 final
            q1q2q4 final
            q1q3q4 final
            q1q2q3q4 final

            --> q1
            q1 -0-> q1
            q1 -1-> q1q2
            
            q1q3 -0-> q1q4
            q1q3 -1-> q1q2q4

            q1q2 -0-> q1q3
            q1q2 -1-> q1q2q3
            
            q1q2q3 -0-> q1q3q4
            q1q2q3 -1-> q1q2q3q4

            q1q4 -0-> q1
            q1q4 -1-> q1q2

            q1q2q4 -0-> q1q3
            q1q2q4 -1-> q1q2q3

            q1q3q4 -0-> q1q4
            q1q3q4 -1-> q1q2q4

            q1q2q3q4 -0-> q1q3q4
            q1q2q3q4 -1-> q1q2q3q4
            

        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)

    def test_case5(self) -> None:
        """
        Test Case 5:
        Comprueba que se procesan correctamente los autómatas que no son deterministas
        con union de estados junto con estados lambdas, es decir se crean uniones de estados
        para sacar los lambdas y esas uniones se vuelven a unir con todos los estados.
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            q1 final
            q2
            q3

            --> q1
            q1 --> q3
            q1 -b-> q2
            
            q2 -a-> q2
            q2 -a-> q3
            q2 -b-> q3

            q3 -a-> q1
            
            
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q1q3 final
            q2
            q2q3
            q3
            q1q2q3 final
            empty

            --> q1q3

            q1q3 -a-> q1q3
            q1q3 -b-> q2

            q2 -a-> q2q3
            q2 -b-> q3

            q2q3 -a-> q1q2q3
            q2q3 -b-> q3

            q1q2q3 -a-> q1q2q3
            q1q2q3 -b-> q2q3

            q3 -a-> q1q3
            q3 -b-> empty

            empty -a-> empty
            empty -b-> empty
            
            

        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


    def test_case6(self) -> None:
        """
        Test Case 6:
        Test que comprueba que se hacen correctamente las uniones con estados finales.
        Es decir, en este test se unen estados no finales con estados finales, y se
        comprueba que se hace correctamente.
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1
            qf final

            --> q0

            q0 -a-> q0
            q0 -b-> q0
            q0 -a-> q1

            q1 -b-> qf
            
            
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q0q1
            q0qf final
            

            --> q0

            q0 -a-> q0q1
            q0 -b-> q0
            
            q0q1 -a-> q0q1
            q0q1 -b-> q0qf
            
            q0qf -a-> q0q1
            q0qf -b-> q0
            
            
            

        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)




    def test_case7(self) -> None:
        """
        Test Case 7:
        Comprueba que se procesan correctamente los autómatas que no son deterministas
        a autómatas deterministas donde una gran parte de las transiciones son de símbolo
        lambda. Así comprobamos que aunque haya una gran conversion de estados en la primera parte,
        es decir, de no determinista con lambdas a no determinista sin lambdas, el autómata se
        sigue procesando correctamente.
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1
            q2
            q3
            q4
            q5
            q6
            q7 final

            --> q0
            q0 --> q1

            q0 --> q5

            q1 -a-> q2

            q2 --> q3

            q3 -b-> q4

            q4 --> q7

            q5 -a-> q6

            q6 --> q7
            
            
            
            
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0q1q5
            q2q3q6q7 final
            q4q7 final
            empty

            --> q0q1q5

            q0q1q5 -a-> q2q3q6q7
            q0q1q5 -b-> empty

            q2q3q6q7 -a-> empty
            q2q3q6q7 -b-> q4q7

            q4q7 -a-> empty
            q4q7 -b-> empty

            empty -a-> empty
            empty -b-> empty
            
            

        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)

        
if __name__ == '__main__':
    unittest.main()


    