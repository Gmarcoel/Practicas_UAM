/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 21-09-2019
 *
 */

#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
/***************************************************/
/* Function: random_num           Date:  05/10/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/

int random_num(int inf, int sup)
{
  int result;
  if (inf == ERR || sup == ERR)
  {
    return ERR;
  }
  result = (rand() % (sup - inf + 1)) + inf;
  return result; 
}


/***************************************************/
/* Function: generate_perm        Date: 05/10/20   */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int N: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N)
{
  int i, aux, j;
  int *perm;
  if (N<=0)
  {
    return NULL;
  }
  perm = malloc(N*sizeof(perm[0]));
  if (perm == NULL)
    return NULL;
  for (i = 0; i < N; i++)
  {
    perm[i] = i + 1;
  }
  for (i = 0; i < N; i++)
  {
    j = random_num(i, N - 1); /*random num*/
    aux = perm[i];            /*auxiliar num*/
    perm[i] = perm[j];
    perm[j] = aux; /*perm*/
  }
  return perm;
}

/***************************************************/
/* Function: generate_permutations   Date: 05/10/20*/
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
  int i, **array;
  if(n_perms<0 || N <=0){
    return NULL;
  }
  array = (int **)calloc(n_perms, sizeof(array[0]));
  /*tenemos que cambiar el calloc por malloc*/
  if (array == NULL)
  {
    return NULL;
  }
  for (i = 0; i < n_perms; i++)
  {
    array[i] = generate_perm(N);
    if (array[i] == NULL)
    {
      i--;
      while (i >= 0)
      {
        free(array[i]);
        i--;
      }
      return NULL;
    }
  }
  return array;
}

/*This function generates a file so we can do an histogram*/
/*
int generate_histogram_file(char *file, int min, int max, int times)
{
  FILE *f;
  int i = 0;
  int arr[max - min + 1];
  f = fopen(file, "w");
  srand(time(NULL));

  for (i = 0; i < max - min + 1; i++)
  {
    arr[i] = 0;
  }

  for (i = 0; i < times; i++)
  {
    arr[random_num(min, max) - min]++;
  }
  for (i = 0; i < max - min + 1; i++)
  {
    fprintf(f, "%d %d\n", i + min, arr[i]);
  }
  fclose(f);
  return 0;
}*/