/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 16/01/20
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
/*
*
*@brief elements of an object
* Defines the id and name of a space
*
*/
typedef struct _Object Object;

#define MAX_OBJECT 100
#define FIRST_OBJECT 1
/***
 * @brief It creates a new object
*
* object_create reserves memory for
* new object if it is created
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param the identification of the object
* @return the object created
*/
Object* object_create(Id id);
/***
 * @brief It destroys an object
*
* object_destroy deletes the object 
* and frees the memory
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param existing object
* @return status check
*/
STATUS object_destroy(Object* object);
/***
 * @brief Searches the object
*
* object_get_id searches the id of the object
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param pointer to the structure object
* @return the id
*/
Id object_get_id(Object* object);
/***
 * @brief It changes the name
*
* object_set_name changes the name of the object
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param pointer to the structure object
* @param name to change
* @return status check
*/
STATUS object_set_name(Object* object, char* name);
/***
 * @brief Searches the name
*
* object_get_name searches the name of the object
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param pointer to the structure object
* @return the name
*/
char* object_get_name(Object* object);
/***
* @brief Changes the description of the object
*
*@date 16/03/20
*@author Javier López
*
* @param pointer to the structure object
* @param description of the object
* @return status
*/
STATUS object_set_description(Object* object, char* description);
/***
* @brief Gets the description of the object
*
*@date 16/03/20
*@author Javier López
*
* @param pointer to the structure object
* @return description of the object
*/
char *object_get_description(Object* object);

/***
 * @brief Gives information of the object
*
* object_print checks if it is possible to print
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param pointer to the structure object
* @return status check
***/
STATUS object_print(Object* object);
/**
 * @brief Searches the position
*
* object_get_location searches for the position of the object
*
*@date 16/01/20
*@author Gonzalo Mejías
*
* @param pointer to the structure object
* @return the id
ESTA FUNCION YA NO EXISTE LA LOCALIZACION DEL OBJETO SE BUSCA DESDE SPACE 
**/

#endif
