#include "set.h"

struct _Set {
	Id id[MAX_IDS];
	Id num_ids;
};

Set* set_create() {
  int i;
  Set *newSet = NULL;

  newSet = (Set *) malloc(sizeof (Set));

  if (newSet == NULL) {
    return NULL;
  }
  newSet->num_ids = 0;

  for(i=0;i<MAX_IDS;i++) {
    newSet->id[i]=-1;
  }

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



STATUS set_addId(Set* set, Id id) {
  int i = 0;

  if (set == NULL) {
    return ERROR;
  }

  while ( set->id[i] != -1){
    i++;
  }

  if (i >= MAX_IDS) {
    return ERROR;
  }

  set->id[i] = id;
  (set->num_ids)++;

  return OK;
}


STATUS set_delId(Set* set,Id id){
int i=0,c=0;
for(i=0;set->id[i]!=NO_ID;i++)
{
  if ( (c == 0) && (set->id[i] == id) )
  {
    set->id[i] = NO_ID;
    c=1;
  }
  if (c == 1){
    if(set->id[i+1] != NO_ID){
      set->id[i] = set->id[i+1];
    } else {
      set->id[i]=NO_ID;
      (set->num_ids)--;      
    }
  }
}
return ERROR;

	/*
  int i = 0;
	if (set == NULL){
		return ERROR;
	}
	while (set->id[i] != id){
		i++;
	}
	if (i >= MAX_IDS) {
    	return ERROR;
  	}
  	set->id[i] = NO_ID;
    (set->num_ids)--;
  return OK;
  */
}

void set_print(FILE* pf,Set* set){
    int i;
    for (i=0;i<MAX_IDS;i++){
	    if (set->id[i]!=-1)	{
	    	    fprintf(pf,"%li\n",set->id[i]);
	    }
    }
    fprintf(pf,"Num Ids: %li\n",set->num_ids);

}

/*Funciones para hace objects*/

Id * set_get_id(Set* set){
  return set->id;
}

STATUS set_is_id(Set* set,Id id){
	int i = 0;
	if (set == NULL){
		return ERROR;
	}
	while (set->id[i] != id){
		i++;
	if (i >= set->num_ids) {
    	return ERROR;
  	}
  }
  return OK;  
}

Id set_get_num(Set * set){
  if(!set){
    return NO_ID;
  }
  return set->num_ids;
}

Id set_get_id_i(Set* set,Id i){
  return set->id[i];
}