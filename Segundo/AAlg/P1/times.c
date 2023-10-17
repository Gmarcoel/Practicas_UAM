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
  double average_ob = 0,dob;
  int **perm=NULL;
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
  startClock=clock();
  if(startClock<=0){
    return ERR;
  }
  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(perm[i], 0, N-1);
    if (ob == ERR)
    {
      for (i=i-1; i >= 0; i--)
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
  endClock=clock();
  if(endClock<=0){
    return ERR;
  }
  if(n_perms!=0){
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
  t = (double)((endClock - startClock) /n_perms)/ CLOCKS_PER_SEC;
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
  int n,i;
  PTIME_AA ptime = NULL;
  int n_times = ((num_max - num_min) / incr) + 1;
    if (method == NULL || n_perms < 0 || num_min < 0 || num_max < 0 || incr < 0 )
  {
    return ERR;
  }


  ptime = (TIME_AA*)malloc(n_times*sizeof(ptime[0]));
  if(ptime == NULL)
  {
    return ERR;
  }
  
  for(i=0,n=num_min;n<=num_max;i++,n = n + incr)
  {
    if(average_sorting_time(method, n_perms, n, &ptime[i]) == ERR)
    {
      free(ptime);
      return ERR;
    }  
  }
  if (save_time_table(file, ptime, n_times)== ERR)
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
  int i=0;
  if((f=fopen(file, "w"))== NULL)
  {
    return ERR;
  }
  for(i=0; i<n_times; i++) {

    if(fprintf(f, "%d  %.3f  %f  %d  %d \n", ptime[i].N, ptime[i].time*1000, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob) == ERR)
    {
      return ERR;
    }
  }
  
  if(fclose(f) == ERR)
  {
    return ERR;
  }
  return 0;


}
