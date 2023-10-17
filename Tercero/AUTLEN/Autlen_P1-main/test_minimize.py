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
        transformed = automaton.to_minimized()
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
        s = Source(temp, filename="./images/minimize/"+testname, format="png")
        s.view()
        
        transformed = automaton.to_minimized()
        
        temp = write_dot(transformed)
        s = Source(temp, filename="./images/minimize/"+testname+"_transformed", format="png")
        s.view()


    def test_case1(self) -> None:
        """
        Test Case 1:
        Test sencillo con gran cantidad de estados para comprobar que funciona correctamente
        el algoritmo de minimización y que los estados semejantes deben ser unidos como un
        único estado
        """
        automaton_str = """
        Automaton:
            Symbols: 01

            a
            b
            c final
            e
            f
            g
            h

            --> a
            a -0-> b
            a -1-> f

            b -0-> g
            b -1-> c

            c -0-> a
            c -1-> c

            e -0-> h
            e -1-> f

            f -0-> c
            f -1-> g

            g -0-> g
            g -1-> e

            h -0-> g
            h -1-> c

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            ae
            bh
            f
            g
            c final

            --> ae
            ae -0-> bh
            ae -1-> f

            bh -0-> g
            bh -1-> c

            f -0-> c
            f -1-> g

            g -0-> g
            g -1-> ae
            
            c -0-> ae
            c -1-> c

        """
        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)

    def test_case2(self) -> None:
        """
        Test Case 2:
        En este test hacemos una comprobación del algoritmo de minimización añadiendo en 
        el autómata original varios estados finales, para comprobar que aun teniendo más
        de un estado final, el algoritmo de minimización sigue funcionando correctamente.
        """
        automaton_str = """
        Automaton:
            Symbols: 01

            a
            b
            c final
            d
            e
            f
            g final

            --> a
            a -0-> b
            a -1-> f

            b -0-> c
            b -1-> e

            c -0-> c
            c -1-> c

            d -0-> a
            d -1-> e

            e -0-> e
            e -1-> e

            f -0-> g
            f -1-> e

            g -0-> g
            g -1-> g
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            a
            bf
            e
            cg final

            --> a
            a -0-> bf
            a -1-> bf

            bf -0-> cg
            bf -1-> e

            e -0-> e
            e -1-> e

            cg -0-> cg
            cg -1-> cg


        """

        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


    def test_case3(self) -> None:
        """
        Test Case 3:
        En este test hacemos una comprobación del algoritmo de minimización en la que
        algunos de los estados generados van a no ser accesibles, por lo que el algoritmo deberá
        eliminarlos.
        """
        automaton_str = """
        Automaton:
            Symbols: 01

            q0
            q1
            q2
            q3 final
            q4
            q5 final

            --> q0
            q0 -0-> q1
            q0 -1-> q3

            q1 -0-> q0
            q1 -1-> q3

            q2 -0-> q1
            q2 -1-> q4

            q3 -0-> q5
            q3 -1-> q5
            
            q4 -0-> q3
            q4 -1-> q3
            
            q5 -0-> q5
            q5 -1-> q5
            

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            q0q1
            q3q5 final

            --> q0q1
            q0q1 -0-> q0q1
            q0q1 -1-> q3q5

            q3q5 -0-> q3q5
            q3q5 -1-> q3q5



        """
        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)




    def test_case4(self) -> None:
        """
        Test Case 4:
        En este test hacemos una comprobación del algoritmo de minimización en la que
        el estado inicial es además de un estado final. En este caso, el algoritmo deberá
        unir los estados no finales con estados finales, y así comprobamos que los estados
        finales se mantienen.
        """
        automaton_str = """
        Automaton:
            Symbols: 12

            q0 final
            q1
            q2
            q3
            q4 final
            q5
            q6 final

            --> q0
            q0 -1-> q1
            q0 -2-> q5

            q1 -1-> q2
            q1 -2-> q3

            q2 -1-> q3
            q2 -2-> q6

            q3 -1-> q4
            q3 -2-> q1
            
            q4 -1-> q1
            q4 -2-> q5
            
            q5 -1-> q3
            q5 -2-> q6

            q6 -1-> q1
            q6 -2-> q5
            

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 12

            q0q4q6 final
            q1
            q2q5
            q3

            --> q0q4q6
            q0q4q6 -1-> q1
            q0q4q6 -2-> q2q5

            q1 -1-> q2q5
            q1 -2-> q3

            q2q5 -1-> q3
            q2q5 -2-> q0q4q6

            q3 -1-> q0q4q6
            q3 -2-> q1



        """
        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


    def test_case5(self) -> None:
        """
        Test Case 5:
        En este test hacemos una comprobación del algoritmo de minimización en la que
        se unen dos estados que tenian transiciones a los mismos estados, y el algoritmo
        deberá eliminar los estados originales para crear uno solo.
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            
            q0
            q1 final
            q2
            

            --> q0
            q0 -a-> q1
            q0 -b-> q0

            q1 -a-> q2
            q1 -b-> q1

            q2 -a-> q1
            q2 -b-> q2

            

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0q2 
            q1 final

            --> q0q2
            q0q2 -a-> q1
            q0q2 -b-> q0q2

            q1 -a-> q0q2
            q1 -b-> q1



        """
        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


    def test_case6(self) -> None:
        """
        Test Case 6:
        En este test hacemos una comprobación del algoritmo de minimización en la que
        comprobamos de nuevo que el algoritmo funciona correctamente. Para ello le damos un
        autómata con diferentes retos como múltiples estados entre los que se unen estados finales.
        """
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final
            q2
            q3 final
            q4
            

            --> q0
            q0 -a-> q1
            q0 -b-> q3

            q1 -a-> q2
            q1 -b-> q1

            q2 -a-> q1
            q2 -b-> q2

            q3 -a-> q4
            q3 -b-> q3
            
            q4 -a-> q3
            q4 -b-> q4
            

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q1q3 final
            q2q4

            --> q0
            q0 -a-> q1q3
            q0 -b-> q1q3

            q1q3 -a-> q2q4
            q1q3 -b-> q1q3
            
            q2q4 -a-> q1q3
            q2q4 -b-> q2q4



        """
        expected = AutomataFormat.read(expected_str)
        self._check_transform(automaton, expected)


if __name__ == '__main__':
    unittest.main()