/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}
/***************************************************/
/* Function: init_dictionary       Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function initializates a dictionary using  */
/* the given dictionary pointer and the given size */
/* and the given order                             */
/*                                                 */
/* Input:                                          */
/* int size: size of dictionary                    */
/* char order: order of the dictionary             */
/*                                                 */
/* Output:                                         */
/* PDICT: returns the initialized dictionary       */
/***************************************************/
PDICT init_dictionary (int size, char order)
{
  
  PDICT pdict = NULL;
  assert(size>0);
  assert(order==NOT_SORTED || order==SORTED);
  pdict = (PDICT)malloc(sizeof(DICT));
  pdict->size = size;
  pdict->order = order;
  pdict->n_data = 0;
  pdict->table = (int*)calloc(size,sizeof(pdict->table));
  return pdict;
}
/***************************************************/
/* Function: free_dictionary       Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function frees the used memory of a given  */
/* dictionary                                      */
/*                                                 */
/* Input:                                          */
/* int PDICT: dictionary to be freed               */
/*                                                 */
/* Output:                                         */
/* void (none)                                     */
/***************************************************/
void free_dictionary(PDICT pdict)
{
  assert(pdict!=NULL);
  free(pdict->table);
  free(pdict);
  return;
}
/***************************************************/
/* Function: insert_dictionary     Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function inserts a given key on a given    */
/* dictionary                                      */
/*                                                 */
/* Input:                                          */
/* int PDICT: dictionary used                      */
/* int key: key to be inserted                     */
/*                                                 */
/* Output:                                         */
/* int: basic operations needed                    */
/***************************************************/
int insert_dictionary(PDICT pdict, int key)
{
  int A,j;
  int last = (pdict->n_data),first = 0;
  int bo = 0;

  assert(pdict!=NULL);
  assert(key>0);

  if(pdict->order == NOT_SORTED) {
    pdict->table[pdict->n_data] = key;
    pdict->n_data=pdict->n_data+1;
  }

  else if(pdict->order == SORTED)
  {    
    pdict->table[pdict->n_data] = key;
    pdict->n_data=pdict->n_data+1;
    A=pdict->table[last];
    j=last-1;
    while (j >= first && pdict->table[j]>A)
    {
      pdict->table[j+1]=pdict->table[j];
      j--;
    }
    pdict->table[j+1]=A;
  } 
  return bo;
}
/***************************************************/
/* Function: massive_insertion_dictionary          */ 
/* Date: 10/12/20                                  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function inserts they keys of an array on  */
/* a dictionary                                    */
/*                                                 */
/* Input:                                          */
/* int PDICT: dictionary used                      */
/* int keys: array of keys to be inserted          */
/* int n_keys: number of keys of the array         */
/*                                                 */
/* Output:                                         */
/* int: error control                              */
/***************************************************/
int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i=0;

  assert(pdict!=NULL);
  assert(keys!=NULL);
  assert(n_keys>0);

  for(i=0; i<n_keys; i++){
    if (insert_dictionary(pdict, keys[i])== ERR)
    {
      return ERR;
    }
  }
  return OK;
}

/***************************************************/
/* Function: search_dictionary     Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function calls a method for dictionary     */
/* searching                                       */
/*                                                 */
/* Input:                                          */
/* int PDICT: dictionary used                      */
/* int key: key to be searched                     */
/* int ppos: position where key is found           */
/*  pfunc_search method: searching method used     */
/*                                                 */
/* Output:                                         */
/* call to the searching method function           */
/***************************************************/
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  assert(pdict!=NULL && key>0 && key<=pdict->n_data && ppos!=NULL && method!=NULL);
  return method(pdict->table, 0, pdict->n_data-1, key, ppos);
}


/* Search functions of the Dictionary ADT */

/***************************************************/
/* Function: bin_search            Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function searches a key on a table         */
/*                                                 */
/* Input:                                          */
/* int *table: Table where key is searched         */
/* int key: key to be inserted                     */
/* int F: first element of the table               */
/* int L: last element of the table                */
/* int key: key to be inserted                     */
/* int ppos: position where key is found           */
/*                                                 */
/*                                                 */
/* Output:                                         */
/* int: basic operations needed                    */
/***************************************************/
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int start=F;
  int end=L;
  int m=0;
  int result=0;
  int ob=0;

  assert(table!=NULL && L>=F && F>=0 && key>=0 && ppos!=NULL);

  while (start<=end){
    m=(start+end)/2;
    result=table[m]-key;
    ob++;
    if(result==0){
      *ppos=m;
      return ob;
    }
    else if(result<0){
      start=m+1;
    }
    else{
      end=m-1;
    }
  }
  *ppos=NOT_FOUND;
  return ob;
}

/***************************************************/
/* Function: lin_search            Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function searches a key on a table         */
/*                                                 */
/* Input:                                          */
/* int *table: Table where key is searched         */
/* int key: key to be inserted                     */
/* int F: first element of the table               */
/* int L: last element of the table                */
/* int key: key to be inserted                     */
/* int ppos: position where key is found           */
/*                                                 */
/*                                                 */
/* Output:                                         */
/* int: basic operations needed                    */
/***************************************************/
int lin_search(int *table,int F,int L,int key, int *ppos )
{
  int i=0,bo = 0;

  assert(table!=NULL && F<=L && F>=0 && key>=0 && ppos!=NULL);

  for(i=F,bo=1; i<L; i++,bo++){
    if(table[i]==key){
      *ppos=i;
      return bo;
    }
  }
  *ppos=NOT_FOUND;
  return bo;
}
/*Private function explained in the end*/
void SwapTables(int a, int b); 
/***************************************************/
/* Function: lin_auto_search       Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function searches a key on a table         */
/*                                                 */
/* Input:                                          */
/* int *table: Table where key is searched         */
/* int key: key to be inserted                     */
/* int F: first element of the table               */
/* int L: last element of the table                */
/* int key: key to be inserted                     */
/* int ppos: position where key is found           */
/*                                                 */
/*                                                 */
/* Output:                                         */
/* int: basic operations needed                    */
/***************************************************/
int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i = 0,bo = 0;
  assert(table!=NULL && F<=L && F>=0 && key>=0);
  for (i=F,bo=1;i<L;i++, bo++)
  {
    if (table[i]==key)
    {
      if(i>0)
      {
        SwapTables(table[i],table[i-1]);
      }
      *ppos=i;
      return bo;
    }
  }
  *ppos=NOT_FOUND;
  return bo;
}
/***************************************************/
/* Function: SwapTables            Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function swaps two elements                */
/*                                                 */
/* Input:                                          */
/* int a: first element to be swaped               */ 
/* int b: second element to be swaped               */ 
/*                                                 */
/* Output:                                         */
/* none (void function)                            */
/***************************************************/
void SwapTables(int a, int b)
{
  int auxiliar = 0;
  assert(a>0 && b>0);
  auxiliar = a;
  a = b;
  b = auxiliar;
  return;
}
