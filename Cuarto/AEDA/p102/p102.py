"""
ALGORITMIA Y ESTRUCTURAS DE DATOS AVANZADAS\n
Group 02\n
Practice 1\n
Authors:\n
\a\a\a*Daniela Varela Sánchez*\n
\a\a\a*Guillermo Martín-Coello Juárez*\n
"""

import numpy as np
from typing import List, Callable


def matrix_multiplication(m1: np.ndarray, m2: np.ndarray):
    """
    This function receives two compatible matrixes and returns the result of the multiplication of the two matrixes, or error if the matrixes are not compatible.
    Implemented using loops.
    \n\tparam m1: First matrix
    \n\tparam m2: Second matrix
    """
    if m1.shape[1] != m2.shape[0]:
        raise ValueError("The matrixes are not compatible")
    else:
        result = np.zeros((m1.shape[0], m2.shape[1]))
        for i in range(m1.shape[0]):
            for j in range(m2.shape[1]):
                for k in range(m2.shape[0]):
                    result[i][j] += m1[i][k] * m2[k][j]
        return result


def rec_bb(t: List, f: int, l: int, key: int) -> int:
    """
    Receives a list and applies a recursive version of the binary search to find the position of the key between
    first and last. If not found, returns None
    \n\tparam t: list to search
    \n\tparam f: first position
    \n\tparam l: last position
    \n\tparam key: key to find
    """
    if f > l:
        return None
    else:
        m = (f + l) // 2
        if t[m] == key:
            return m
        elif t[m] < key:
            return rec_bb(t, m + 1, l, key)
        else:
            return rec_bb(t, f, m - 1, key)


def bb(t: List, f: int, l: int, key: int):
    """
    Receives a list and applies a iterative version of the binary search to find the position of the key between
    first and last. If not found, returns None
    \n\tparam t: list to search
    \n\tparam f: first position
    \n\tparam l: last position
    \n\tparam key: key to find
    """
    while f <= l:
        m = (f + l) // 2
        if t[m] == key:
            return m
        elif t[m] < key:
            f = m + 1
        else:
            l = m - 1
    return None


# 2A

def min_heapify(h: np.ndarray, i: int):
    """
    Receives an array h of Numpy and aplies the operation of heapify to the element situated in position i
    \n\tparam h: array of elementes
    \n\tparam i: position to heapify
    """
    l = 2 * i + 1
    r = 2 * i + 2
    if l < len(h) and h[l] < h[i]:
        smallest = l
    else:
        smallest = i
    if r < len(h) and h[r] < h[smallest]:
        smallest = r
    if smallest != i:
        h[i], h[smallest] = h[smallest], h[i]
        min_heapify(h, smallest)


def insert_min_heap(h: np.ndarray, k: int) -> np.ndarray:
    """
    Receives an array h of Numpy and a key k and inserts the key in the array
    \n\tparam h: array of elementes
    \n\tparam k: key to insert
    """
    h = np.append(h, k)
    i = len(h) - 1
    while i > 0 and h[(i - 1) // 2] > h[i]:
        h[i], h[(i - 1) // 2] = h[(i - 1) // 2], h[i]
        i = (i - 1) // 2
    return h


def create_min_heap(h: np.ndarray):
    """
    Receives an array h of Numpy and creates a min heap
    \n\tparam h: array of elementes
    """
    for i in range(len(h) // 2, -1, -1):
        min_heapify(h, i)

# 2B


def pq_ini():
    """
    Initializes a priority queue
    """
    return np.array([])


def pq_insert(h: np.ndarray, k: int) -> np.ndarray:
    """
    Inserts an element k in priority queue h and returns the queue
    \n\tparam h: array of elements
    \n\tparam k: element to insert
    """
    return insert_min_heap(h, k)


def pq_remove(h: np.ndarray) -> tuple[int, np.ndarray]:
    """
    Removes the minimum element of the priority queue h and returns the queue
    \n\tparam h: array of elements
    """
    if len(h) == 0:
        raise ValueError("The priority queue is empty")
    else:
        h[0], h[-1] = h[-1], h[0]
        min = h[-1]
        h = np.delete(h, -1)
        min_heapify(h, 0)
    return min, h

# 2C


def select_min_heap(h: np.ndarray, k: int) -> int:
    """
    This function gets the element that would be in position 'k' if the 'h' given array was ordered
    \n\tparam h: array of elements
    \n\tparam k: position of the wanted element in the sorted array
    """
    # Change the array to its negative
    h = -h
    # Create a min heap with the first k elements
    create_min_heap(h[:k])
    # For each element in the array, if it is larger than the root of the
    # heap, replace the root with the element and heapify
    for i in range(k, len(h)):
        if h[i] > h[0]:
            h[0] = h[i]
            min_heapify(h[:k], 0)
    # Return the root of the heap
    return -h[0]




