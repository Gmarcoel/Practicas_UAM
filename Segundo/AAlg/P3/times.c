/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include <time.h>
#include "permutations.h"
#include "search.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>
/***************************************************/
/* Function: average_sorting_time  Date: 15/10/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function adds the corresponding fields to   */
/* the structure ptime, adding its number of        */
/* permutations, the size of the permutations, the  */
/* average execution time, the average number of    */
/* times OB was executed alongside with the minimum */
/* amount of times and the maximum                  */
/*                                                 */
/* Input:                                          */
/* pfunc_ordena metodo: function of the method we  */
/* want to use                                     */
/* int n_perms: Number of permutations to be made  */
/* int N: number of elements in every permutation  */
/* Output:                                         */
/* short: It returns ON (0) if everything goes as  */
/* planned and ERR (-1) if there has been an error */
/***************************************************/
short average_sorting_time(pfunc_ordena metodo, int n_perms, int N, PTIME_AA ptime) 
{

  int i = 0;
  clock_t startClock;
  clock_t endClock;
  double t;
  int ob;
  int min_ob = INT_MAX, max_ob = 0;
  double average_ob = 0, dob;
  int **perm = NULL;
  ptime->N = N;
  ptime->n_elems = n_perms;
  if (metodo == NULL || n_perms < 0 || N < 0 || ptime == NULL)
  {
    return ERR;
  }
  perm = generate_permutations(n_perms, N);
  if (perm == NULL)
  {
    return ERR;
  }
  startClock = clock();
  if (startClock == -1)
  {
    return ERR;
  }
  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(perm[i], 0, N - 1);
    if (ob == ERR)
    {
      for (i = i - 1; i >= 0; i--)
      {
        free(perm[i]);
      }
      free(perm);
      return ERR;
    }
    if (ob < min_ob)
    {
      min_ob = ob;
    }
    if (ob > max_ob)
    {
      max_ob = ob;
    }
    dob = (double)ob;
    average_ob = average_ob + dob;
  }
  endClock = clock();
  if (endClock == -1)
  {
    return ERR;
  }
  if (n_perms != 0)
  {
    average_ob = (average_ob / (double)n_perms);
  }

  for (i = 0; i < n_perms; i++)
  {
    free(perm[i]);
  }
  free(perm);
  ptime->max_ob = max_ob;
  ptime->min_ob = min_ob;
  ptime->average_ob = average_ob;
  t = (double)((endClock - startClock) / n_perms) / CLOCKS_PER_SEC;
  ptime->time = t;
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times                */
/* Date: 17/10/20                                  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function generates a table of permutations */
/* and then it calls the average sorting time      */
/* function so it adds its corresponding values to */
/* its corresponding fields. Afterwards it makes a */
/* file where it stores the the average clock time,*/
/* and the average, minimum and maximum times that */
/* OB was called using the method method           */
/*                                                 */
/* Input:                                          */
/* pfunc_ordena metodo: function of the method we  */
/* want to use                                     */
/* int n_perms: Number of permutations to be made  */
/* int num_min: minimun number of elements in the  */
/* permutations                                    */
/* int num_max: maximun number of elements in the  */
/* permutations                                    */
/* incr: increment value of elements in the        */
/* permutations                                    */
/*                                                 */
/* Output:                                         */
/* short: It returns ON (0) if everything goes as  */
/* planned and ERR (-1) if there has been an error */
/***************************************************/
short generate_sorting_times(pfunc_ordena method, char *file, int num_min, int num_max, int incr, int n_perms)
{
  int n, i;
  PTIME_AA ptime = NULL;
  int n_times = ((num_max - num_min) / incr) + 1;
  if (method == NULL || n_perms < 0 || num_min < 0 || num_max < 0 || incr < 0)
  {
    return ERR;
  }

  ptime = (TIME_AA *)malloc(n_times * sizeof(ptime[0]));
  if (ptime == NULL)
  {
    return ERR;
  }

  for (i = 0, n = num_min; n <= num_max; i++, n = n + incr)
  {
    if (average_sorting_time(method, n_perms, n, &ptime[i]) == ERR)
    {
      free(ptime);
      return ERR;
    }
  }
  if (save_time_table(file, ptime, n_times) == ERR)
  {
    free(ptime);
    return ERR;
  }
  free(ptime);

  return 0;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/* Date: 17/10/20                                  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function generates a file file where it    */
/* stores the size, the average clock time and     */
/* and minimum times OB is executed for each ptimme*/
/*                                                 */
/* Input:                                          */
/* char *file: File to be written in               */
/* PTIME_AA ptime: variable to store time data     */
/* int ntimes: number of times the calculations    */
/* are done                                        */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  FILE *f;
  int i = 0;
  if ((f = fopen(file, "w")) == NULL)
  {
    return ERR;
  }
  for (i = 0; i < n_times; i++)
  {

    if (fprintf(f, "%d  %.3f  %.2f  %d  %d \n", ptime[i].N, ptime[i].time * 1000, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob) == ERR)
    {
      return ERR;
    }
  }

  if (fclose(f) == ERR)
  {
    return ERR;
  }
  return 0;
}
/***************************************************/
/* Function: average_search_time  Date: 10/12/20  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function adds the corresponding fields to  */
/* the structure ptime, adding its number of       */
/* keys, the size, the average execution time      */
/* , the average number of times OB was executed   */
/*  alongside with the minimum                     */
/* amount of times and the maximum                 */
/*                                                 */
/* Input:                                          */
/* pfunc_search method: function of the method we  */
/* want to use                                     */
/* pfunc_key_generator generator: function of the  */
/* generator we want to use                        */
/* int n_times: nº of times the keys generated with*/
/* the key generator are searched                  */
/* int N: number of elements in every permutation  */
/* Output:                                         */
/* short: It returns ON (0) if everything goes as  */
/* planned and ERR (-1) if there has been an error */
/***************************************************/
short average_search_time(pfunc_search method, pfunc_key_generator generator, char order, int N, int n_times, PTIME_AA ptime)
{
  /*Variables*/
  int max_ob = 0;
  int min_ob = INT_MAX;
  double average_ob = 0;
  clock_t startClock;
  clock_t endClock;
  double t;
  int *perm = NULL;
  int *table = NULL;
  int ob;
  double dob;
  int i;
  int ppos;
  PDICT d = NULL;


  assert(method!=NULL && generator!=NULL && N>0 && n_times>0 && ptime!=NULL);

  /*1. Create a dictionary of size N.*/
  d = init_dictionary(N, order);
  if (d == NULL)
  {
    return ERR;
  }
  /*2. Create a permutation of size N using the generate perm routine.*/
  perm = generate_perm(N);
  if (perm == NULL)
  {
    free_dictionary(d); /*ESTO ES UN VOID NO ME DIGAS QUE META CONTROL DE ERRORES PORQUE LA FUNCION VIENE PREDEFINIDA*/
    return ERR;
  }
  /*3. Using the massive insertion dictionary, insert the elements in the permutation into the dictionary.*/
  if(massive_insertion_dictionary(d, perm, N)==ERR){
    free_dictionary(d);
    free(perm);
    return ERR;
  }
  /*4. Allocate memory for the table containing the n times*N keys to search in the 1 to N range.*/
  table = (int *)malloc((n_times * N) * sizeof(table[0]));
  if (table == NULL)
  {
    free_dictionary(d);
    free(perm);
    return ERR;
  }
  /*5. Fill the previous table with the n times*N keys to search using the key generator.(Note: the key generators
create numbers from 1 to N, so it is important that permutations also contain numbers from 1 to N*/
  generator(table,N*n_times,N);

  /*6. Measure the time (clock y BOs) that the search method takes to search the n times*N keys stored in the previously mentioned table.*/
  startClock = clock();
  if (startClock <= 0)
  {
    free_dictionary(d);
    free(perm);
    free(table);
    return ERR;
  }
  for (i = 0; i < N * n_times; i++)
  {
    ob = search_dictionary(d, table[i], &ppos, method);
    if (ob == ERR)
    {
      free_dictionary(d);
      free(perm);
      free(table);
      return ERR;
      ;
    }
    if (ob < min_ob)
    {
      min_ob = ob;
    }
    if (ob > max_ob)
    {
      max_ob = ob;
    }
  
    dob = (double)ob;
    average_ob = average_ob + dob;
  }
  endClock = clock();
  if (endClock == -1)
  {
    free(perm);
    free(table);
    free_dictionary(d);

    return ERR;
  }
  average_ob=average_ob/(N*n_times);
  /*7. Properly fill the fields of the ptime structure.*/
  ptime->max_ob = max_ob;
  ptime->min_ob = min_ob;
  ptime->average_ob = average_ob;
  t = (double)((endClock - startClock)*1000/ (N*n_times))/CLOCKS_PER_SEC;
  ptime->time = t;
  ptime->N = N;
  ptime->n_elems = N * n_times;
  /*8. Free the allocated memory and exit the function*/
  free(perm);
  free(table);
  free_dictionary(d);
  return OK;
}
/***************************************************/
/* Function: generate_search_times                */
/* Date: 09/12/20                                  */
/* Authors: Guillermo Martin-coello & Daniel Varela*/
/*                                                 */
/* This function generates a ptime array           */
/* and then it calls the average search time       */
/* function so it adds the results in each         */
/* iteration of the ptime array, changing the N    */
/* value in each from F to L with an increment of  */
/* in on each call. Then it calls the save time    */
/* table function to store the data                */
/*                                                 */
/* Input:                                          */
/* pfunc_search method: function of the method we  */
/* want to use                                     */
/* int n_times: Number of times each key is       */
/* searched                                        */
/* int num_min: minimun number of elements in the  */
/* permutations                                    */
/* int num_max: maximun number of elements in the  */
/* permutations                                    */
/* incr: increment value of elements in the        */
/* permutations                                    */
/* char *file: file where data will be stored      */
/*                                                 */
/* Output:                                         */
/* short: It returns ON (0) if everything goes as  */
/* planned and ERR (-1) if there has been an error */
/***************************************************/
short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char *file, int num_min, int num_max, int incr, int n_times)
{
  int n, i;
  PTIME_AA ptime = NULL;
  int icreamy = ((num_max - num_min)/incr)+1 ;

  if (method == NULL || num_min < 0 || num_max < 0 || incr < 0)
  {
    return ERR;
  }

  ptime = (TIME_AA *)malloc(icreamy * sizeof(ptime[0]));
  if (ptime == NULL)
  {
    return ERR;
  }

  for (i = 0, n = num_min; n <= num_max; i++, n = n + incr)
  {
    
    if (average_search_time(method, generator, order, n, n_times, &ptime[i]) == ERR)
    {
      free(ptime);
      return ERR;
    }
  }
    if (save_time_table(file, ptime, icreamy) == ERR)
    {
      free(ptime);
     return ERR;
   }
  free(ptime);

  return 0;
}
