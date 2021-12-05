/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/***************************************************/
/* Function: InsertSort            Date: 18/10/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function orders the table given by the input*/
/* table from the smallest number to the biggest    */
/* using insertsort algorithm                       */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int InsertSort(int *table, int ip, int iu)
{
  int aux, i, j, ob = 0;
  if (table == NULL || ip == -1 || iu == -1)
  {
    return ERR;
  }
  for (i = ip + 1; i <= iu; i++)
  {
    aux = table[i];

    j = i - 1;
    while (j >= ip && ob++ && table[j] > aux)
    {
      table[j + 1] = table[j];
      j--;
    }
    table[j + 1] = aux;
  }
  return ob;
}

/***************************************************/
/* Function: InsertSortInv         Date: 18/10/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function orders the table given by the input*/
/* table from the largest number to the smallest    */
/* using insertsort algorithm                       */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int InsertSortInv(int *table, int ip, int iu)
{
  int aux, i, j, ob = 0;
  if (table == NULL || ip == -1 || iu == -1)
  {
    return ERR;
  }
  for (i = ip + 1; i <= iu; i++)
  {
    aux = table[i];
    j = i - 1;
    while (j >= ip && ob++ && table[j] < aux)
    {
      table[j + 1] = table[j];
      j--;
    }
    table[j + 1] = aux;
  }
  return ob;
}
