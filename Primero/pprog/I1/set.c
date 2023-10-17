#include "set.h"

struct _Set {
	Id id[MAX_IDS];
	Id num_sets;
};

Set* set_create(Id id) {

  Set *newSet = NULL;

  if (id == NO_ID)
    return NULL;

  newSet = (Set *) malloc(sizeof (Set));

  if (newSet == NULL) {
    return NULL;
  }
  newSet->id[0] = id;
  newSet->num_sets = 1;

  return newSet;
}

STATUS set_destroy(Set* set) {
  if (!set) {
    return ERROR;
  }

  free(set);
  set = NULL;

  return OK;
}



STATUS set_add_id(Set* set, Id id) {
  int i = 0;

  if (set == NULL) {
    return ERROR;
  }

  while ( set->id[i] == -1){
    i++;
  }

  if (i >= MAX_IDS) {
    return ERROR;
  }

  set->id[i] = id;

  return OK;
}



STATUS set_del_id(Set* set,Id id){
	int i = 0;
	if (set == NULL){
		return ERROR;
	}
	while (set->id[i] =! id){
		i++;
	}
	if (i >= MAX_IDS) {
    	return ERROR;
  	}
  	set->id[i] = -1;
}