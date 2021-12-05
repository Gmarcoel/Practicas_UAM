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
  BOOL Movable;
  BOOL Hidden;
  Id Open;
  BOOL Illuminate;
  BOOL TurnedOn;
  Id Dependency;
  Id Incompatible;
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
  newObject->Movable = FALSE;
  newObject->Hidden = FALSE;
  newObject->Open = NO_ID;
  newObject->Illuminate = FALSE;
  newObject->TurnedOn = FALSE;
  newObject->Dependency = NO_ID;
  newObject->Incompatible = NO_ID;

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

char *object_get_description(Object *object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}

BOOL object_get_propMovable(Object* object) {

  if (!object) return FALSE;

  return object->Movable;
}

STATUS object_set_propMovable(Object *object, BOOL prop) {

  if (!object || (prop != 1 && prop != 0))
    return ERROR;

  object->Movable = prop;

  return OK;
}

BOOL object_get_propHidden(Object *object) {

  if (!object) return FALSE;

  return object->Hidden;
}

STATUS object_set_propHidden(Object *object, BOOL prop) {

  if (!object || (prop != 1 && prop != 0))
    return ERROR;

  object->Hidden = prop;

  return OK;
}

Id object_get_propOpen(Object *object) {

  if (!object) return NO_ID;

  return object->Open;
}

STATUS object_set_propOpen(Object *object, Id prop) {

  if (!object)
    return ERROR;

  object->Open = prop;

  return OK;
}

BOOL object_get_propIlluminate(Object *object) {

  if (!object) return FALSE;

  return object->Illuminate;
}

STATUS object_set_propIlluminate(Object *object, BOOL prop) {

  if (!object || (prop != 1 && prop != 0))
    return ERROR;

  object->Illuminate = prop;

  return OK;
}

BOOL object_get_propTurnedOn(Object *object) {

  if (!object) return FALSE;

  return object->TurnedOn;
}

STATUS object_set_propTurnedOn(Object *object, BOOL prop) {

  if (!object || (prop != 1 && prop != 0))
    return ERROR;

  object->TurnedOn = prop;

  return OK;
}

STATUS object_print(Object* object) {
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}

Id object_get_propDependency(Object *object) {
 
  if (!object)
    return NO_ID;

  return object->Dependency;
}

STATUS object_set_propDependency(Object *object, Id prop) {

  if (!object)
    return ERROR;

  object->Dependency = prop;

  return OK;
}

Id object_get_propIncompatible(Object *object) {

  if (!object) 
    return NO_ID;

  return object->Incompatible;
}

STATUS object_set_propIncompatible(Object *object, Id prop) {

  if (!object)
    return ERROR;

  object->Incompatible = prop;

  return OK;
}

