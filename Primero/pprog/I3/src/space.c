/** 
 * @brief It defines a space
 * 
 * @file space.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  char description[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Set * objects;
  char icon[WORD_SIZE + 1];
  char icon2[WORD_SIZE + 1];
  char icon3[WORD_SIZE + 1];  
};

Space* space_create(Id id) {

  Space *newSpace = NULL;


  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';
  newSpace->description[0] = '\0';
  newSpace->icon[0] = '\0';
  newSpace->icon2[0] = '\0';
  newSpace->icon3[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->objects = set_create();

  return newSpace;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }
  set_destroy(space->objects);
  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_icon(Space* space, char* icon) {
  if (!space || !icon) {
    return ERROR;
  }

  if (!strcpy(space->icon, icon)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_icon2(Space* space, char* icon) {
  if (!space || !icon) {
    return ERROR;
  }

  if (!strcpy(space->icon2, icon)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_icon3(Space* space, char* icon) {
  if (!space || !icon) {
    return ERROR;
  }

  if (!strcpy(space->icon3, icon)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_linkNorth(Space* space, Id id) { /*Bello is not sure*/
  if (!space) {
    return ERROR; 
  }
  space->north = id;
  return OK;
}

STATUS space_set_linkSouth(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_linkEast(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_linkWest(Space* space,Id id) {
  if (!space) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/* Funcion obsoleta
STATUS space_set_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  set_addId(space->objects,value);
  return OK;
}
*/

char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

STATUS space_set_description(Space* space, char* description) {
  if (!space || !description) {
    return ERROR;
  }

  if (!strcpy(space->description, description)) {
    return ERROR;
  }

  return OK;
}

char * space_get_description(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->description;
}

const char * space_get_icon(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->icon;
}

const char * space_get_icon2(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->icon2;
}

const char * space_get_icon3(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->icon3;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Id space_get_linkNorth(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Id space_get_linkSouth(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Id space_get_linkEast(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Id space_get_linkWest(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

/* Funcion obsoleta
Id space_get_object(Space* space) {
  if (!space) {
    return NO_ID;
  }
	return space->objects;
}
*/

/*Funciones nuevas para OBJECTS*/

STATUS space_add_object(Space* space, Id id) {

  if (space == NULL || id == NO_ID) {
    return ERROR;
  }
  
  return set_addId(space->objects, id);
}

STATUS space_del_object(Space* space,Id id){

	if (space == NULL || id == NO_ID){
		return ERROR;
	}

  return set_delId(space->objects,id);
}

Id* space_get_objects(Space* space){
  if ( space == NULL ){
    return NULL;
  }
  return set_get_id(space->objects);
}

STATUS space_is_object (Space* space, Id id){
  if (space == NULL || id == NO_ID){
    return ERROR;
  }
  return set_is_id(space->objects,id);
}

Set * space_get_object_set(Space* space){
  if (space == NULL){
    return ERROR;
  }
  return space->objects; 
}

/*Aqui acaban las chapucillas de los objetos*/
STATUS space_print(Space* space) {
return OK;
}
/*
STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_LinkNorth(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_LinkSouth(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_LinkEast(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_LinkWest(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }
  
  if (space_get_objects(space)[0]) {
    fprintf(stdout, "---> Objects in the space.\n");
    set_print(space->objects);*/ /*
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
*/
