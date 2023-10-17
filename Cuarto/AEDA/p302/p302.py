
"""
ALGORITMIA Y ESTRUCTURAS DE DATOS AVANZADAS\n
Group 02\n
Practice 3n
Authors:\n
\a\a\a*Daniela Varela Sánchez*\n
\a\a\a*Guillermo Martín-Coello Juárez*\n
"""

import numpy as np
import itertools
from typing import List, Dict, Callable, Iterable, Tuple, Union

## I-A. Basic QuickSelect ##
############################


def split(t: np.ndarray) -> Tuple[np.ndarray, int, np.ndarray]:
    """
    Distributes the elements of t between two arrays with the elements less and greater 
    than t[0] and returns a tuple with the minor elements, the element t[0] and the major elements
    \n\tparam t: Array of elements to be distributed
    \n\t
    \n\treturn: Tuple including the minor elements, the element t[0] and the major elements
    """
    print(t)
    if t == []:
        return ([], None, [])
    mid = t[0]
    t_l = [u for u in t if u < mid]
    t_r = [u for u in t if u > mid]
    return (t_l, mid, t_r)


def qsel(t: np.ndarray, k: int) -> Union[int, None]:
    """
    recursively apply the QuickSelect algorithm using the split function above 
    and return the value of the element to occupy index k in an order of t if that 
    element exists and None if not.
    \n\tparam t: Array of elements to be distributed
    \n\tparam k: Index of the element to be returned
    \n\t
    \n\treturn: Value of the element to occupy index k or None
    """
    if len(t) <= k or t == []:
        return None
    t_l, mid, t_r = split(t)
    m = len(t_l)
    # if t_l == [] or t_r == []: # Esto es una mierda y esta tambien en la version nr
    #     return None

    if k == m:
        return mid
    elif k < m and t_l != []:
        return qsel(t_l, k)
    elif t_r != []:
        return qsel(t_r, k-m-1)
    else:
        return None


def qsel_nr(t: np.ndarray, k: int) -> Union[int, None]:
    """
    Apply the QuickSelect algorithm without recursion using the split function above 
    and return the value of the element to occupy index k in an order of t if that 
    element exists and None if not.
    \n\tparam t: Array of elements to be distributed
    \n\tparam k: Index of the element to be returned
    \n\t
    \n\treturn: Value of the element to occupy index k or None
    """
    while len(t) > k:
        t_l, mid, t_r = split(t)
        m = len(t_l)
        if k == m:
            return mid
        elif k < m and t_l != []:
            t = t_l
        elif t_r != []:
            t = t_r
            k = k-m-1
        else:
            return None
    return None


## I-B. QuickSelect 5 ##
########################

def split_pivot(t: np.ndarray, mid: int) -> Tuple[np.ndarray, int, np.ndarray]:
    """
    Split function that uses the mid value to divide t.
    \n\tparam t: Array of elements to be distributed
    \n\tparam mid: The element to be used as pivot
    \n\t
    \n\treturn: Tuple including the minor elements, the element t[mid] and the major elements
    """
    if t == []:
        return ([], None, [])
    t_l = [u for u in t if u < mid]
    t_r = [u for u in t if u > mid]
    return (t_l, mid, t_r)


def pivot5(t: np.ndarray) -> int:
    """
    that returns the "pivot 5" of the array t according to the procedure 
    "median of means of 5 elements" and calling to the function qsel5_nr 
    defined below.
    \n\tparam t: Array of elements to be distributed
    \n\t
    \n\treturn: Index of the pivot
    """
    if t == []:
        return None
    if len(t) < 5:
        # if even number of elements, add the min element to the array
        if (len(t) % 2 == 0):
            t = np.append(t, np.min(t))
        return np.median(t)

    # Split T arrays of 5 elements
    t_5 = [t[i:i+5] for i in range(0, len(t), 5)]

    # For each subtable Ti obtain its median mi
    medians = []
    for el in t_5:
        if (len(el) % 2 == 0):
            medians.append(np.min(medians))
        medians.append(np.median(el))
    return pivot5(medians)


def qsel5_nr(t: np.ndarray, k: int) -> Union[int, None]:
    """
    which returns the element in the index k of an order of t using 
    the pivot5 functions, split_pivot above.
    \n\tparam t: Array of elements to be distributed
    \n\tparam k: Index of the element to be returned
    \n\t
    \n\treturn: Value of the element to occupy index k or None
    """
    while len(t) > k:
        t_l, mid, t_r = split_pivot(t, pivot5(t))
        m = len(t_l)
        if k == m:
            return mid
        elif k < m and t_l != []:
            t = t_l
        elif t_r != []:
            t = t_r
            k = k-m-1
        else:
            break
    return None

## I-C. QuickSort 5 ##
######################


def qsort_5(t: np.ndarray) -> np.ndarray:
    """
    Use the above functions split_pivot, pivot_5 to return an order of Table T.
    \n\tparam t: Array of elements to be distributed
    \n\t
    \n\treturn: Ordered array
    """
    # if (low < high) {

    if len(t) > 1:
        # Split
        t_l, mid, t_r = split_pivot(t, pivot5(t))
        # Separately sort elements before
        # partition and after partition
        ret = np.append(qsort_5(t_l), int(mid))
        ret = np.append(ret, qsort_5(t_r))
        return ret
    else:
        return np.array(t)


def edit_distance(str_1: str, str_2: str) -> int:
    """
    Returns the edit distance between the two strings str_1 and str_2.
    \n\tparam str_1: First string
    \n\tparam str_2: Second string
    \n\t
    \n\treturn: Edit distance between str_1 and str_2
    """
    matrix = [list(range(0, len(str_1)+1))]
    for i in range(1, len(str_2)+1):
        matrix.append([i])
        j = 1
        while j < len(str_1)+1:
            if str_1[j-1] == str_2[i-1]:
                matrix[i].append(matrix[i-1][j-1])
            else:
                matrix[i].append(
                    1+min([matrix[i-1][j-1], matrix[i][j-1], matrix[i-1][j]]))
            j += 1

    return matrix[len(str_2)][len(str_1)]


def max_subsequence_length(str_1: str, str_2: str) -> int:
    """
    Returns the length of the longest subsequence common to str_1 and str_2, even is not contiguous. The function
    should use as little memory as possible.
    \n\tparam str_1: First string
    \n\tparam str_2: Second string
    \n\t
    \n\treturn: Length of the longest subsequence common to str_1 and str_2
    """

    x = str_1
    y = str_2
    """ Calculate  the LCS length between sequences x and y using
    matrix dynamic programming. Return matrix. """

    e = np.zeros((len(x)+1, len(y)+1), dtype=int)

    for i in range(1, len(x)+1):
        for j in range(1, len(y)+1):
            # x[i] == y[j]
            if (x[i-1] == y[j-1]):
                e[i, j] = 1 + e[i-1, j-1]

            # x[i] != y[j]
            else:
                e[i, j] = max(e[i-1, j], e[i, j-1])
    return e[-1,-1]



def max_common_subsequence(str_1: str, str_2: str) -> str:
    """
    Returns the length of the longest subsequence common to str_1 and str_2, even is not contiguous. The function
    should use as little memory as possible.
    \n\tparam str_1: First string
    \n\tparam str_2: Second string
    \n\t
    \n\treturn: Max common subsequence
    """
    matrix = [["" for i in range(0, len(str_1)+1)]]

    for i in range(1, len(str_2)+1):
        matrix.append([""])
        j = 1
        while j < len(str_1)+1:
            if str_1[j-1] == str_2[i-1]:
                matrix[i].append(matrix[i-1][j-1] + str_1[j-1])
            else:
                if len(matrix[i][j-1]) > len(matrix[i-1][j]):
                    matrix[i].append(matrix[i][j-1])
                else:
                    matrix[i].append(matrix[i-1][j])

            j += 1
    return matrix[len(str_2)][len(str_1)]


def min_mult_matrix(l_dims: List[int]) -> int:
    """
    Returns the minimal number of multiplications necessary to multiply n matrices whose dimensions are contained
    in the list l_dims with n+1 elements: the first element is the number of rows of the first matrix, and the others are
    the number of columns of the n matrices.
    \n\tparam l_dims: List of dimensions of the matrices
    \n\t
    \n\treturn: Minimal number of multiplications
    """
    matrix = [[0 for i in range(0, len(l_dims))]
              for j in range(0, len(l_dims))]
    for i in range(1, len(l_dims)):
        matrix[i][i] = 0
    for l in range(2, len(l_dims)):
        for i in range(1, len(l_dims)-l+1):
            j = i+l-1
            matrix[i][j] = float("inf")
            for k in range(i, j):
                q = matrix[i][k]+matrix[k+1][j]+l_dims[i-1]*l_dims[k]*l_dims[j]
                if q < matrix[i][j]:
                    matrix[i][j] = q
    return matrix[1][len(l_dims)-1]
