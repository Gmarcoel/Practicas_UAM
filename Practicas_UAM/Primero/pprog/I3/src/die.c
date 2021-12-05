/**
* @brief it defines a die
*
* @file die.c
* @author Gonzalo Mejías
* @version 1.0
* @date 20/02/20
*/

#include <stdlib.h>
#include <time.h>
#include "set.h"

typedef struct die{
	Id id;
	int max;
	int min;
	int num_obtained;
}Die;

void die_init(void){
	srand(time(NULL));
}

Die * die_create(Id id) {

  Die * newDie = NULL;

  if (id == NO_ID)
    return NULL;

  newDie = (Die *) malloc(sizeof (Die));

  if (newDie == NULL) {
    return NULL;
  }
  newDie->id = id;
  newDie->num_obtained = 0;
  srand(time(NULL));

  return newDie;
}

STATUS die_destroy(Die * d) {
  
  if (!d) {
    return ERROR;
  }

  free(d);
  d = NULL;

  return OK;
}

int die_roll(Die * d){

	if(!d){
		return -1;
	}

	d->num_obtained = 1+(rand( ) % 6);

	return d->num_obtained;
}

int die_last_value(Die* die)
{
  if(!die) return -1;
  
  return die->num_obtained;
}

STATUS die_print(Die * die) {

  if (!die) {
    return ERROR;
  }

  fprintf(stdout, "--> d (Id: %ld; num_obtained: %d)\n", die->id, die->num_obtained);

  return OK;
}








