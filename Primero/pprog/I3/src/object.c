/** 
 * @brief It defines an object
 * 
 * @file object.c
 * @author Gonzalo Mejías
 * @version 1.0 
 * @date 16/01/20
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"

struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
  char description[WORD_SIZE + 1];
};

Object* object_create(Id id) {

  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) {
    return NULL;
  }
  newObject->id = id;

  newObject->name[0] = '\0';
  newObject->description[0] = '\0';
  return newObject;
}

STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

STATUS object_set_description(Object* object, char* description) {
  if (!object || !description) {
    return ERROR;
  }

  if (!strcpy(object->description, description)) {
    return ERROR;
  }

  return OK;
}

char * object_get_description(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}


STATUS object_print(Object* object) {
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
