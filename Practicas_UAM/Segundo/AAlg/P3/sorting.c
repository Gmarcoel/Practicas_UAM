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

/***************************************************/
/* Function: MergeSort         Date: 04/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function orders the table given by the input*/
/* table from the smallest number to the biggest   */
/* using mergesort algorithm                       */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/*                                                 */
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int MergeSort(int *table, int ip, int iu)
{
  int ob = 0, m;
  assert(ip <= iu);
  if (ip == iu)
    return OK;

  m = ((ip + iu) / 2);
  ob = ob + MergeSort(table, ip, m);
  ob = ob + MergeSort(table, m + 1, iu);
  ob = ob + Merge(table, ip, iu, m);
  return ob;
}
/***************************************************/
/* Function: Merge             Date: 04/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This merges two ordered parts of the table      */
/* table from the smallest number to the biggest   */
/* sorting both tables                             */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* int imiddle: the element that is in the middle  */
/* of the table (or the one to the right if it's   */
/* even)                                           */
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/

int Merge(int *table, int ip, int iu, int imiddle)
{
  int ob = 0;
  int *taux;
  int i, j, k;
  assert(iu >= imiddle);
  assert(imiddle >= ip);
  taux = (int *)calloc(1 + iu - ip, sizeof(taux[0]));
  if (taux == NULL)
  {
    return ERR;
  }

  i = ip;
  j = imiddle + 1;
  k = 0;

  while (i <= imiddle && j <= iu)
  {
    ob++;                         
    if (table[i] < table[j]) /*OB*/
    {
      taux[k] = table[i];
      i++;
    }
    else
    {
      taux[k] = table[j];
      j++;
    }
    k++;
  }

  if (i > imiddle) 
  {
    while (j <= iu) 
    {
      taux[k] = table[j];
      j++;
      k++;
    }
  }
  else if (j > iu)
  {
    while (i <= imiddle)
    {
      taux[k] = table[i];
      i++;
      k++;
    }
  }
  for (i = ip, j = 0; i <= iu; i++, j++)
  {
    table[i] = taux[j];
  }
  free(taux);
  return ob;
}
/***************************************************/
/* Function: QuickSort         Date: 05/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function orders the table given by the input*/
/* table from the smallest number to the biggest   */
/* using QuickSort algorithm                       */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/*                                                 */
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int QuickSort(int *table, int ip, int iu)
{
  int bo = 0,aux;
  int pos;
  assert(iu >= ip); 
  if (ip > iu)
  {
    return ERR;
  }
  if (ip == iu)
  {
    return 1;
  }
  else
  {
    if ((aux = Split(table, ip, iu, &pos))== ERR) return ERR;
    bo = bo + aux;
    if (ip < pos - 1)
    {
    if((aux = QuickSort(table, ip, pos - 1))==ERR) return ERR;
    bo = bo + aux;
    }
    if (pos + 1 < iu)
    {
      if((aux = QuickSort(table, pos + 1, iu))==ERR) return ERR;
    bo = bo + aux;
    }
    return bo;
  }
  
  return ERR;
}


int Swap(int *a, int *b);
int Median(int *table, int ip, int iu, int *pos);

/***************************************************/
/* Function: Split             Date: 5/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function Splits the given table using      */
/* the Median function and Swaps the elements      */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* int *pos: pointer that will be returned with    */
/* the value of the Median after the Split function*/
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int Split(int *table, int ip, int iu, int *pos)
{
  int i, m, k, bo=0;
  assert(iu >= ip);
  if(Median(table, ip, iu, pos)== ERR) return ERR;
  m = *pos; 
  k = table[m];

  if ( Swap(&(table[ip]), &(table[m])) == ERR ) return ERR;

  m = ip;
  for (i = ip + 1; i <= iu; i++)
  {
    bo++;
    if (table[i] < k) /*  BO  */
    {
      m++;
      if ( Swap(&(table[i]), &(table[m])) == ERR ) return ERR;
      

    }
  }
  if ( Swap(&(table[ip]), &(table[m])) == ERR ) return ERR;
  *pos = m;
  return bo;
}



/***************************************************/
/* Function: Median            Date: 05/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function recieves two pointers and swaps   */
/* their values                                    */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* int *a: pointer to one of the values to swap    */
/* int *b: pointer to the other value to swap      */
/* Output:                                         */
/* int: It returns OK if everything goes right and */
/* ERR (-1) if something goes wrong                */
/***************************************************/
int Swap(int *a, int *b)
{
  int auxiliar;
  if (a==NULL || b == NULL)
  {
    return ERR;
  }
  auxiliar = *a;
  *a = *b;
  *b = auxiliar;
  return OK;
}



/***************************************************/
/* Function: Median            Date: 05/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function assigns the pivot, in this case   */
/* the first position (ip) to the pointer pos      */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* int *pos: pointer that will be returned with    */
/* the value of ip                                 */
/* Output:                                         */
/* int: It returns 0 if everything goes right and  */
/* ERR (-1) if something goes wrong                */
/***************************************************/
int Median(int *table, int ip, int iu, int *pos){
  assert (table!=NULL);
  assert (ip<iu);
  assert (pos!=NULL);
  *pos=ip;
  return 0;
}



/***************************************************/
/* Function: QuickSort_ntr     Date: 06/11/20      */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function orders the table given by the input*/
/* table from the smallest number to the biggest   */
/* using QuickSort algorithm but getting rid of    */
/* the tail recusrion                              */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* int table: array with all the values            */
/* int ip: first element of the table              */
/* int iu: last element of the table               */
/* int *pos: pointer that will be returned with    */
/* the value of the Median after the Split function*/
/* Output:                                         */
/* int: It returns an integer containig tne amount */
/* of basic operations realized and ERR (-1) if    */
/* something goes wrong                            */
/***************************************************/
int QuickSort_ntr(int *table, int ip,int iu)
{
    int pos,aux;
    int bo=0;
    assert(iu >= ip); 
    if(table == NULL)
    {
      return ERR;
    }
    while (ip<iu)
    {
        if((aux=Split(table, ip, iu, &pos)) == ERR) return ERR;
        bo+=aux;
        if(ip<pos-1){
          if((aux=QuickSort_ntr(table, ip, pos-1)) == ERR) return ERR;
        bo += aux;
        }
        ip=pos+1;
    }
    return bo;
}