/***
 * @brief Inventory functions library
 * @file inventory.h
 * @author Gabriela Trabajo
 * @version 1.0 
 * @date 21/03/20
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

/***
*@brief It creates a new inventory.
*@date 21/03/20
*@author Gabriela Trabajo de Rada
*@param id identification of the inventory
*@return a pointer to a new inventory
*/
Inventory* inventory_create();

/***
*@brief It destroys an already existing inventory.
*@date 21/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory that you want to destroy
*@return OK if it was destroyed correctly or ERROR if not
*/
STATUS inventory_destroy(Inventory *in);

/***
*@brief It adds a new object id to the inventory (set).
*@date 21/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory you want to modify
*@param id Identification of the object that you want to add
*@return OK if it was added correctly or ERROR if not
*/
STATUS inventory_add_object(Inventory *in, Id id);

/***
*@brief It searches for the id especified on the inventory.
*@date 21/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory
*@param id Id of the object
*@return OK if the object belongs to the set or ERROR if not
*/
STATUS inventory_is_object(Inventory *in, Id id);

/***
*@brief It prints all the content of an inventory.
*@date 21/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory you want to print
*@return OK if it was printed correctly or ERROR if not
*/
STATUS inventory_print(Inventory *in);

/***
*@brief It deletes an object from the inventory.
*@date 22/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory
*@param id Id of the object to delete
*@return OK if it was deleted correctly or ERROR if not
*/
STATUS inventory_del_object(Inventory *in, Id id);

/***
*@brief It gets the max number of objects of the inventory.
*@date 22/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory
*@return Max number of objects or -1 if there was an error
*/
int inventory_get_maxobj(Inventory *in);

/***
*@brief It changes the max number of objects in the inventory.
*@date 22/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory
*@param i New max number
*@return OK if it was changed correctly or ERROR if not
*/
STATUS inventory_set_maxobj(Inventory *in, int i);

/***
*@brief It gets the number of objects of the inventory.
*@date 22/03/20
*@author Gabriela Trabajo de Rada
*@param in Pointer to the inventory
*@return Number of objects or -1 if there was an error
*/
int inventory_get_NumObjects(Inventory *in);

/***
*@brief gives a number of objects
*@date 22/03/20
*@author Guillermo Martín
*@param in Pointer to the inventory
*@return pointer to the objects
*/
Id *inventory_get_objects(Inventory *in);

/***
*@brief It gets the objects of the inventory.
*@date 22/03/20
*@author Javier López
*@param in Pointer to the inventory
*@return pointer to the set of objects
*/
Set *inventory_get_object_set(Inventory *in);

#endif