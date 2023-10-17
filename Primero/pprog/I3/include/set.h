#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define MAX_IDS 1064

typedef struct _Set Set;

/*Functions*/


/**
* @brief It initialized a new set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param none
* @return the initialized set
*/
Set* set_create();
/**
* @brief Destroys set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @return status check
*/
STATUS set_destroy(Set* set);
/**
* @brief adds an id to the set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @param id added id
* @return status check
*/
STATUS set_addId(Set* set, Id id);
/**
* @brief deletes an id to the set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @param id removed id
* @return status check
*/
STATUS set_delId(Set* set, Id id);
/**
* @brief prints a set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param pf file where set is printed
* @param set printed set
* @return void
*/
void set_print(FILE* pf,Set* set);

/*Funciones para objetos*/

/**
* @brief returns set ids
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set 
* @return ids array with set ids
*/
Id* set_get_id(Set* set);
/**
* @brief checks id id exists on set
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @param id to be checked
* @return status check
*/
STATUS set_is_id(Set* set,Id id);
/**
* @brief return number of ids
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @return number of ids
*/
int set_get_num(Set * set);
/**
* @brief search an id
*
* @date 01/03/20
* @author Guillermo Martín
*
* @param set
* @param id id
* @return int
*/
int set_search_id (Set *set, Id id);

#endif