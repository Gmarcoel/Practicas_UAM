
"""Automaton implementation."""
from enum import Flag
from typing import Collection, get_args
from time import sleep

from automata.interfaces import (
    AbstractFiniteAutomaton,
    AbstractState,
    AbstractTransition,
)


class State(AbstractState):
    """State of an automaton."""

    # You can add new attributes and methods that you think that make your
    # task easier, but you cannot change the constructor interface.


class Transition(AbstractTransition[State]):
    """Transition of an automaton."""

    # You can add new attributes and methods that you think that make your
    # task easier, but you cannot change the constructor interface.

modified = {}

class FiniteAutomaton(
    AbstractFiniteAutomaton[State, Transition],
):
    """Automaton."""

    def __init__(
        self,
        *,
        initial_state: State,
        
        states: Collection[State],
        symbols: Collection[str],
        transitions: Collection[Transition],
    ) -> None:
        super().__init__(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
        )

        # Add here additional initialization code.
        # Do not change the constructor interface.
    

    def to_deterministic(
        self,
    ) -> "FiniteAutomaton":
        global modified
        
        for state in self.states:
            # Lee todos los estados a los que se llega con lambda
            estadosLambda = _complete_lambdas(self, state)
            # Para cada estado lambda
            nombres = []
            nombres.append(state.name)
            for estadoLambda in estadosLambda:
                nombres.append(estadoLambda.name)
                # Si es final
                if estadoLambda.is_final == True:
                    state.is_final = True
                # Copia las transiciones del estado lambda
                aux = list(self.transitions)
                for transicion in self.transitions:
                    if estadoLambda == transicion.initial_state:
                        t = Transition(state, transicion.symbol, transicion.final_state)
                        aux.append(t)
                self.transitions = aux
            # Renombra el estado
            state.name = get_name(nombres)
                
            # Destruir las del estado
            aux = list(self.transitions)
            for transicion in self.transitions:
                if transicion.initial_state == state and transicion.symbol == None:
                    aux.remove(transicion)
            self.transitions = aux


        # Pasar de no determinista sin lambdas a determinista
        # ----------------------------------------------------------------------
        #
        # Creamos lista de estados
        estados = []
        # Diccionario de nombres modificados
        estados.append(self.initial_state)
        empty = State(name="empty",is_final=False)
        auxTransitions = []
        auxTransitions = list(self.transitions)
        for simbolo in self.symbols:
            auxTransitions.append(Transition(empty, simbolo, empty))
        # Bucle que itera sobre los estados de la lista de estados
        simbolos = []
        simbolos += list(self.symbols)
        #simbolos.append(None)
        
        c_estados = 0
        l_estados = len(estados)
        while c_estados < l_estados:
            # Bucle de simbolos posibles
            for simbolo in simbolos:
                transicionesFusionadas = []
                # Bucle de todas las transiciones de auxTransitions
                destinos = []
                for transicion in auxTransitions:
                    # En caso que la transicion tenga como estado inicial el estado y el símbolo que estamos analizando, añadimos a lista destino
                    if transicion.initial_state==estados[c_estados] and transicion.symbol == simbolo:
                        transicionesFusionadas.append(transicion)
                        # Este if es un parche
                        if transicion.final_state not in destinos:
                            destinos.append(transicion.final_state)
                # Llamar a función de fusión de estados con el argumento destinos (esta fusionara si hay mas destinos en uno)
                #fusion(destinos, estados, l_estados, auxTransitions,simbolo)
                # ----------------------------------------------------------------------
                # Fusiona estados
                # Si no hay destinos, no hace nada
                # Si solo hay un destino, lo coge como un estado en vez de como una lista
                mayorQueUno = False      
                if len(destinos) == 0:
                    if empty not in estados:
                        estados.append(empty)
                        l_estados += 1
                    transicion = Transition(estados[c_estados],simbolo,empty)
                    nuevoEstado = empty
                    auxTransitions.append(transicion)

                elif len(destinos) == 1:
                    nuevoEstado = destinos[0]
                
                # Si hay mas de un destino, se fusiona

                elif len(destinos) > 1:
                    destinos.sort(key = sortName)
                    nombre = ""
                    names = []


                    nuevoEstado = State(nombre, is_final=False)
                    for destino in destinos:
                        names.append(destino.name)
                        if destino.is_final == True:
                            nuevoEstado.is_final = True
                            # break asesino

                    nuevoEstado.name = get_name(names)
                    
                    # auxTransitions =  [t for t in auxTransitions if t not in transicionesFusionadas]
                    # nuevaTransicion = Transition(estados[c_estados],simbolo,nuevoEstado)
                    # auxTransitions.append(nuevaTransicion)
                    mayorQueUno = True

                # Si estado no esta en lista estados lo añadimos
                flag = False
                if len(destinos) > 0:
                    for nombre in estados:
                        if nombre.name == nuevoEstado.name:
                            flag = True
                            if mayorQueUno:
                                nuevoEstado = nombre
                            break
                    
                    if mayorQueUno:
                        auxTransitions =  [t for t in auxTransitions if t not in transicionesFusionadas]
                        nuevaTransicion = Transition(estados[c_estados],simbolo,nuevoEstado)
                        #print(str(transicionesFusionadas)+" PASA AHORA A SER "+str(nuevaTransicion))
                        auxTransitions.append(nuevaTransicion)
                    
                    if not flag:
                        transitionsToAdd = []
                        for est in destinos:
                            for transicion in auxTransitions:
                                if transicion.initial_state == est:
                                    # transitionsToRemove.append(transicion)
                                    
                                    nuevaTransicion = Transition(nuevoEstado, transicion.symbol, transicion.final_state) 
                                    if nuevaTransicion not in transitionsToAdd:
                                        transitionsToAdd.append(nuevaTransicion)

                        auxTransitions += transitionsToAdd
                            
                        
                        estados.append(nuevoEstado)
                        l_estados += 1
            c_estados += 1    
            
        # ----------------------------------------------------------------------
        self.transitions = auxTransitions      
        self.states = estados
        # Eliminar las transiciones repetidas
        aux = []
        for t in auxTransitions:
            if t not in aux:
                aux.append(t)
        auxTransitions = aux
        # Eliminar estados a los que no se llega
        aux = []
        for transicion in auxTransitions:
            if transicion.initial_state in estados and transicion.final_state in estados:
                aux.append(transicion)
        
        auxTransitions = aux
        nuevoAutomata = FiniteAutomaton(initial_state=self.initial_state, states=estados, symbols=self.symbols, transitions=auxTransitions)
        return nuevoAutomata






    def to_minimized(
        self,
    ) -> "FiniteAutomaton":
        """ 
        raise NotImplementedError("This method must be implemented.")
        states = []
        states += list(self.states)
        indexx= 0
        indexy= len(states)-2
        table = []
        auxList = []
        obsolete = []
        while indexx<len(states)-2:
            indexy = len(states)-2-indexx
            auxList=[]
            while indexy>=0
                for transition in self.transitions:
                    if transition.initial_state == states[indexx] and transition.final_state == states[indexy]:
                        auxList.append(indexy)
                indexy -=1
            table.append(auxList) 
            for connectionList in table:
                if auxList == connectionList:
                    obsolete.append(states[indexy])
            indexx += 1
            """
        #While (No hay cambios)
        #    While (no hay celdas vacías en Q’)
        #        Identificar inicio clase
        #        Desde la clase primera hasta la máxima en esta iteración
        #            Marcar las celdas que siguen en cada clase anterior
        #        Para todas las celdas vacías
        #            Asignamos una nueva clase
        #            Marcamos todas las vacías que estaban en la misma clase y comprobamos si siguen en esta clase nueva
        estados = []
        estados.append(self.initial_state)
        c_estados = 0
        l_estados = len(estados)
        while c_estados < l_estados:
            for transicion in self.transitions:
                if transicion.initial_state == estados[c_estados]:
                    if transicion.final_state not in estados:
                        estados.append(transicion.final_state)
                        l_estados+=1
            c_estados += 1

        trans = []
        for transicion in self.transitions:
            if transicion.initial_state not in estados or transicion.final_state not in estados:
                trans.append(transicion)
        
        self.states = estados
        self.transitions = [t for t in self.transitions if t not in trans]



        # Creamos tabla con grupos
        grupos = []

        # Primera ronda
        # --------------
        # Creamos grupos
        no_f = []
        f = []
        for state in self.states:
            if state.is_final:
                f.append(state)
            else:
                no_f.append(state)
        grupos.append(no_f)
        grupos.append(f)

        # Algoritmo
        # ----------------

        # Bucle activo hasta que se interrumpa
        while 1:
            # Creamos una tabla para los nuevos grupos
            nuevosGrupos = []
            # Loop de grupos
            for grupo in grupos:
                i1 = 1
                for estado in grupo:
                    # Se crea el nuevo grupo de este estado
                    isInGroup = False
                    for compGrupo in nuevosGrupos:
                        if estado in compGrupo:
                            isInGroup = True
                            break
                    if isInGroup==False:
                        nuevoGrupo = []
                        nuevoGrupo.append(estado)
                        # Loop de estados 2 (los que quedan despues del loop anterior osea si el uno va por B este empieza en C)
                        # Loop de estados
                        i2 = i1
                        while i2 < len(grupo):
                            # Bucle transiciones para obtener todas las interesantes
                            t1 = None
                            t2 = None
                            sameGroup = True
                            for simbolo in self.symbols:
                                for transicion in self.transitions:
                                    if transicion.symbol == simbolo and transicion.initial_state == estado:
                                        t1 = transicion
                                    elif transicion.symbol == simbolo and transicion.initial_state == grupo[i2]:
                                        t2 = transicion

                                if t1 == None or t2 == None:
                                    print("Transition error")
                                else:
                                    for g in grupos:
                                        if t1.final_state not in g and t2.final_state in g:
                                            sameGroup = False
                                            break
                            # Si todos los simbolos llevan a los mismos grupos
                            if sameGroup:
                                # Se añaden los estados al nuevo grupo
                                nuevoGrupo.append(grupo[i2])
                            # Si no no se hace nada
                            i2 += 1
                        # Se añade el nuevo grupo creado
                        nuevosGrupos.append(nuevoGrupo)
                    i1 += 1
            # Una vez se hayan hecho todos los grupos se comprueba si los grupos nuevos son iguales a los antiguos
            if compararGrupos(grupos,nuevosGrupos): # Esto esta un poco mal
                # Si si se crea un nuevo automata con los nuevos estados
                #return modificarAutomata(self, nuevosGrupos)
                return modificarAutomata(self, nuevosGrupos)
                
                
            # Si no se repite con los nuevos grupos
            else:
                grupos = nuevosGrupos
        

    
def modificarAutomata(self, grupos):
    transiciones = list(self.transitions)
    estados = []
    transicionesEliminar = []
    for grupo in grupos:
        if len(grupo) == 1:
            estados.append(grupo[0])
        else:
            # Creamos el nuevo estado
            nuevoEstado = grupo[0]
            nombres = []
            for estado in grupo:
                nombres.append(estado.name)
                if estado.is_final:
                    nuevoEstado.is_final = True
            nuevoEstado.name = get_name(nombres)
            # Cambiamos las transiciones
            for transicion in transiciones:
                if transicion.initial_state in grupo and transicion.final_state in grupo:
                    transicion.initial_state = nuevoEstado
                    transicion.final_state = nuevoEstado
                elif transicion.initial_state in grupo:
                    transicion.initial_state = nuevoEstado
                elif transicion.final_state in grupo:
                    transicion.final_state = nuevoEstado
            estados.append(nuevoEstado)

    # Aplicamos cambios
    self.states = estados

    aux = []
    for t in transiciones:
        if t not in transicionesEliminar and t not in aux:
            aux.append(t)
        
    transiciones = aux
    self.transitions = transiciones
    return self
    
                


def compararGrupos(g1,g2):
    if len(g1) != len(g2):
        return False
    for i in range(len(g1)):
        if len(g1[i]) != len(g2[i]):
            return False
        for j in range(len(g1[i])):
            if g1[i][j] != g2[i][j]:
                return False
    return True

    

                

def sortName(e):
  return e.name


def get_name(oldnames):
    global modified
    names = []
    for n in oldnames:
        if n in modified:
            names += list(modified[n])
        else:
            names.append(n)
    names.sort()
    aux = []
    for name in names:
        if name not in aux:
            aux.append(name)
    names = aux
    final = ""
    for name in names:
        final += name

    
    modified[final] = names
    return final



def printear_estados(estados):
    print("************")
    print("Estados:")
    print("************")
    for estado in estados:
        print(estado.name)
        print(estado.is_final)
        print("-------------------------")
    

def printear_transiciones(transiciones):
    print("************")
    print("Transiciones:")
    print("************")
    for transicion in transiciones:
        print(transicion.initial_state.name)
        print(transicion.symbol)
        print(transicion.final_state.name)
        print("-------------------------")






def _complete_lambdas(self, state):
    aux = []
    aux.append(state)
    l = 1
    i = 0
    while i < l:
        for transition in self.transitions:
            if transition.symbol == None and transition.initial_state==aux[i]:
                aux.append(transition.final_state)
                l += 1
        i += 1
    aux.remove(state)
    return aux