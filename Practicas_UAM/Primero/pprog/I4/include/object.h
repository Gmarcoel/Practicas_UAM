/** 
 * @brief It defines an object
 * 
 * @file object.h
 * @author Gonzalo Mejías
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

#define MAX_OBJECT 500
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
* @brief Gets the property "movable" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object is movable "TRUE", if not "FALSE"
*/
BOOL object_get_propMovable(Object *object);
/***
* @brief Sets the property "movable" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop boolean to set the new state of the property
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propMovable(Object *object, BOOL prop);
/***
* @brief Gets the property "hidden" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object is hidden "TRUE", if not "FALSE"
*/
BOOL object_get_propHidden(Object *object);
/***
* @brief Sets the property "hidden" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop boolean to set the new state of the property
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propHidden(Object *object, BOOL prop);
/***
* @brief Gets the property "open" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object can open, returns de id of the link. If not, returns "NO_ID"
*/
Id object_get_propOpen(Object *object);
/***
* @brief Sets the property "open" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop id to set the new id of the link you can open
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propOpen(Object *object, Id prop);
/***
* @brief Gets the property "illuminate" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object can illuminate "TRUE", if not "FALSE"
*/
BOOL object_get_propIlluminate(Object *object);
/***
* @brief Sets the property "illuminate" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop boolean to set the new state of the property
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propIlluminate(Object *object, BOOL prop);
/***
* @brief Gets the property "turnedon" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object is turnedon returns "TRUE", if not "FALSE"
*/
BOOL object_get_propTurnedOn(Object *object);
/***
* @brief Sets the property "turnedon" of the object
*
* @date 27/04/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop boolean to set the new state of the property
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propTurnedOn(Object *object, BOOL prop);
/***
* @brief Gives information of the object
*
* object_print checks if it is possible to print
*
* @date 16/01/20
* @author Gonzalo Mejías
*
* @param pointer to the structure object
* @return status check
***/
STATUS object_print(Object *object);
/***
* @brief Gets the property "dependency" of the object
*
* @date 06/05/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object depends on other, returns de id of that object. If not, returns "NO_ID"
*/
Id object_get_propDependency(Object *object);
/***
* @brief Sets the property "dependency" of the object
*
* @date 06/05/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop id to set the new id of the object to depend on
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propDependency(Object *object, Id prop);
/***
* @brief Gets the property "incompatible" of the object
*
* @date 06/05/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @return if the object is incompatible with other, returns de id of that object. If not, returns "NO_ID"
*/
Id object_get_propIncompatible(Object *object);
/***
* @brief Sets the property "incompatible" of the object
*
* @date 06/05/20
* @author Gabriela Trabajo de Rada
*
* @param object pointer to the structure object
* @param prop id to set the new id of the incompatible object
* @return if it was changed correctly, returns "OK". If not, returns "ERROR"
*/
STATUS object_set_propIncompatible(Object *object, Id prop);

#endif
