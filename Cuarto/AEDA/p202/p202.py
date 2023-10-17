
"""
ALGORITMIA Y ESTRUCTURAS DE DATOS AVANZADAS\n
Group 02\n
Practice 2\n
Authors:\n
\a\a\a*Daniela Varela Sánchez*\n
\a\a\a*Guillermo Martín-Coello Juárez*\n
"""

import numpy as np
import itertools
from typing import List, Dict, Callable, Iterable

# I. Disjoint sets and conected components
########################################################################################
def init_cd(n: int) -> np.ndarray:
    """
    Returns an array with values -1 in the positions {0,1,...,n-1}.
    \n\tparam n: Size of array
    \n\t
    \n\treturn: Initialized array with values -1
    """
    if not n or n <= 0:
        return np.full(1,-1, int)
    return np.full(n,-1, int)


def union(rep_1: int, rep_2: int, p_set: np.array) -> int:
    """
    Returns the representative of the set obtained with the rank-union of the sets represented by the indices rep_1
    and rep_2 in the disjoint set structure represented by the array p_set
    \n\tparam rep_1: Index of the representative of the first set
    \n\tparam rep_2: Index of the representative of the second set
    \n\tparam p_set: Disjoint set structure
    \n\t
    \n\treturn: Representative of the set obtained with the rank-union of the sets represented by the indices rep_1
    """
    if p_set[rep_1] < p_set[rep_2]:
        p_set[rep_2] = rep_1
        return rep_1
    elif p_set[rep_1] > p_set[rep_2]:
        p_set[rep_1] = rep_2
        return rep_2
    else:
        p_set[rep_2] = rep_1
        p_set[rep_1] -= 1
        return rep_1
"""
    if p_set[rep_1-1] < p_set[rep_2-1]:
        p_set[rep_2-1] = rep_1
        return rep_1
    elif p_set[rep_1-1] > p_set[rep_2-1]:
        p_set[rep_1-1] = rep_2
        return rep_2
    else:
        p_set[rep_2-1] = rep_1
        p_set[rep_1-1] -= 1
        return rep_1
"""

def find(ind: int, p_set: np.ndarray) -> int:
    """
    Returns the representative of the element of index ind in the disjoint set structure p_set carrying out path
    compression.
    \n\tparam ind: Index of the element
    \n\tparam p_set: Disjoint set structure
    \n\t
    \n\treturn: Representative of the element of index ind in the disjoint set structure p_set carrying out path
    """
    while p_set[ind] >= 0:
        ind = p_set[ind]
    return ind


def cd_2_dict(p_set: np.array) -> Dict:
    """
    Returns a python dictionary in which the keys are the representatives of the sets, and where the value associated
    to a key u is a list with the elements of the set represented by u (oncluding u itself).
    \n\tparam p_set: Disjoint set structure
    \n\t
    \n\treturn: Dictionary with the connected components
    """
    d = {}
    for i in range(len(p_set)):
        rep = find(i, p_set)
        if rep in d:
            d[rep].append(i)
        else:
            d[rep] = [i]
    return d

# I-B Disjoint sets and connected components
def ccs(n: int, l: List) -> Dict:
    """
    Returns the connected components of a graph. The function will initialized a disjoint set structure with a set per
    node, will run through the edges of the graph and if the two extrema of the edge belong to different sets will join
    them. When all the edges have been processed, the function will convert the structure into a dictionary and return it.
    \n\tparam n: Number of nodes
    \n\tparam l: List of edges
    \n\t
    \n\treturn: Dictionary with the connected components
    """
    # Initialize disjoint set structure
    p_set = init_cd(n)
    for edge in l:
        # Join of each edge
        union(find(edge[0],p_set), find(edge[1],p_set), p_set)
    return cd_2_dict(p_set)


# II. The Traveling Salesman Problem
########################################################################################

# II-A Nearest neighbors algorithm
def dist_matrix(n_nodes: int, w_max=10)-> np.ndarray:
    """
    Generates the distance matrix for a graph of n cities; distances are integers with a maxium value w_max. Keep in
    mind that the matrix must be symmetric and have zeros on the diagonal. For the generation you can use numpy
    functions such as np.random.randint of fill_diagonal
    \n\tparam n_nodes: Number of nodes
    \n\tparam w_max: Maximum weight
    \n\t
    \n\treturn: Distance matrix
    """
    # np.random.randint(low, high, (rows, columns))
    matrix = np.random.randint(1, w_max, (n_nodes, n_nodes))
    np.fill_diagonal(matrix, 0)
    # make symmetric
    matrix = (matrix + matrix.T) // 2

    return matrix

def greedy_tsp(dist_m: np.ndarray, node_ini=0)-> List:
    """
    Receives the distance matrix and returns the circuit given the initial node. The result must be a list of integers
    between 0 and n-1, where n is the number of nodes.
    \n\tparam dist_m: Distance matrix
    \n\tparam node_ini: Initial node
    \n\t
    \n\treturn: Circuit
    """
    num_cities = dist_m.shape[0]
    circuit = [node_ini]
    while len(circuit) < num_cities:
        current_city = circuit[-1]
        # sort cities in ascending distance from current
        options = list( np.argsort(dist_m[ current_city ]) )
        # add first city in sorted list not visited yet
        for city in options:
            if city not in circuit:
                circuit.append(city)
                break
    return circuit + [node_ini]


def len_circuit(circuit: List, dist_m: np.ndarray)-> int:
    """
    that receives the circuit and the distance matrix and returns the length of the circuit.
    \n\tparam circuit: Circuit
    \n\tparam dist_m: Distance matrix
    \n\t
    \n\treturn: Length of the circuit
    """
    length = 0
    for i in range(len(circuit)-1):
        length += dist_m[circuit[i]][circuit[i+1]]
    return length

def repeated_greedy_tsp(dist_m: np.ndarray)-> List:
    """
    Trick to improve the result of the algorithm is to apply the function greedy_tsp starting with all
    the nodes, and return the shortest circuit. Write a function
    \n\tparam dist_m: Distance matrix
    \n\t
    \n\treturn: Circuit
    """
    circuits = []
    for i in range(dist_m.shape[0]):
        circuits.append(greedy_tsp(dist_m, i))
    lengths = [len_circuit(circuit, dist_m) for circuit in circuits]
    return circuits[np.argmin(lengths)]

def exhaustive_greedy_tsp(dist_m: np.ndarray)-> List:
    """
    Implements this idea using the itertools library. Among the iteration functions of the library, there is the
    function permutations(iterable, r=None), that returns an iterable that produces all the permutations of length r
    in lexicographic order. By detfault, r is the length of the iterable passed as a parameter, so all the permitations are
    generated.
    \n\tparam dist_m: Distance matrix
    \n\t
    \n\treturn: Circuit
    """

    circuits = []
    for perm in itertools.permutations(range(1, dist_m.shape[0])):
        circuits.append([0] + list(perm) + [0])
    lengths = [len_circuit(circuit, dist_m) for circuit in circuits]
    return circuits[np.argmin(lengths)]


# Funciones para hacer que el test disfuncional funcione
def connected_comps(n: int, l: List) -> Dict:
    return ccs(n, l)

def exhaustive_tsp(dist_m: np.ndarray)-> List:
    return exhaustive_greedy_tsp(dist_m)