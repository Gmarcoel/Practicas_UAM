/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H
#include "set.h"
#include "types.h"
#include "link.h"
/*
*
*@brief elements of a space
* Defines the ids and name of a space
*
*/
typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1
/**
*@brief It creates a new space
*
* space_create reserves memory for
* new space if it is created
*
*@date 13/01/15
*@author Instructors
*
* @param the identification of the space
* @return the space created
*/
Space* space_create(Id id);
/**
* @brief It destroys a space
*
* space_destroy deletes the space 
* and frees the memory
*
*@date 13/01/15
*@author Instructors
*
* @param existing space
* @return status check
*/
STATUS space_destroy(Space* space);
/**
* @brief Searches the id 
*
* space_get_id searches the id of the space
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_id(Space* space);
/**
* @brief It changes the name
*
* space_set_name changes the name of the space
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param name to change
* @return status check
*/
STATUS space_set_name(Space* space, char* name);
/**
* @brief Searches the name
*
* space_get_name searches the name of the space
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return the name
*/
char* space_get_name(Space* space);
/**
* @brief It changes position
*
* space_set_name changes the position of
* north in the structure
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkNorth(Space* space, Id id);
/**
* @brief Searches the north value 
*
* space_get_north searches in the north
* of the player position
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkNorth(Space* space);
/**
* @brief It changes position
*
* space_set_name changes the position of 
* south in the strcuture
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkSouth(Space* space, Id id);
/**
*@brief Searches the south value 
*
* space_get_south searches in the south
* of the player position
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkSouth(Space* space);
/***
* @brief It changes position
*
* space_set_name changes the position of
* east in the structure
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkEast(Space* space, Id id);
/**
*@brief Searches the east value 
*
* space_get_east searches in the east
* of the player position
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkEast(Space* space);
/**
* @brief It changes position
*
* space_set_name changes the position of
* west in the structure
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkWest(Space* space,Id id);
/**
* @brief Searches the west value 
*
* space_get_west searches in the west
* of the player position
*
* @date 13/01/15
* @author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkWest(Space* space);
/**
* @brief It changes position
*
* space_set_name changes the position of
* up in the structure
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkUp(Space* space,Id id);
/**
* @brief Searches the west value 
*
* space_get_ searches in the west
* of the player position
*
* @date 13/01/15
* @author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkUp(Space* space);
/**
* @brief It changes position
*
* space_set_name changes the position of
* west in the structure
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_linkDown(Space* space,Id id);
/**
* @brief Searches the west value 
*
* space_get_west searches in the west
* of the player position
*
* @date 13/01/15
* @author Instructors
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_linkDown(Space* space);
/**
* @brief changes space description
*
* @date 13/03/20
* @author Javier López
*
* @param space 
* @param description space description
* @return status check
*/
STATUS space_set_description(Space* space, char* description);
/**
* @brief returns space description
*
* @date 13/03/20
* @author Javier López
*
* @param space
* @return description
*/
char * space_get_description(Space* space);
/**
* @brief changes space description2
*
* @date 28/04/20
* @author Gonzalo Mejías
*
* @param space 
* @param description space description
* @return status check
*/
STATUS space_set_description2(Space* space, char* description);
/**
* @brief returns space description2
*
* @date 28/04/20
* @author Gonzalo Mejías
*
* @param space
* @return description
*/
char * space_get_description2(Space* space);

/*Funciones de object*/

/**
* @brief add object to space
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space 
* @param id object id
* @return status check
*/
STATUS space_add_object(Space* space, Id id);
/**
* @brief delete object from space
* @date 13/03/20
* @author Guillermo Martín
*
* @param space 
* @param id object id
* @return status check
*/
STATUS space_del_object(Space* space,Id id);
/**
* @brief return array with all object ids from space
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space 
* @return id array
*/
Id* space_get_objects(Space* space);
/**
* @brief check if object is in space
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space 
* @param id object idd
* @return status check
*/
STATUS space_is_object(Space* space, Id id);
/**
* @brief return set with all objects
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space 
* @return set
*/
Set *space_get_object_set(Space* space);
/**
* @brief changes space icon 1
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @param icon 
* @return status check
*/
STATUS space_set_icon(Space* space, char* icon);
/**
* @brief return space's icon 1
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @return char icon
*/
const char * space_get_icon(Space* space);
/**
* @brief changes space icon 2
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @param icon 
* @return status check
*/
STATUS space_set_icon2(Space* space, char* icon);
/**
* @brief return space's icon 2
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @return char icon
*/
const char * space_get_icon2(Space* space);
/**
* @brief changes space icon 3
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @param icon 
* @return status check
*/
STATUS space_set_icon3(Space* space, char* icon);
/**
* @brief return space's icon 3
*
* @date 13/03/20
* @author Guillermo Martín
*
* @param space  
* @return char icon
*/
const char * space_get_icon3(Space* space);
/**
* @brief sets the ilumination of a space
*
* @date 27/04/20
* @author Javier Lopez
*
* @param space  
* @param bool
* @return STATUS
*/
STATUS space_setIlumination(Space *s,BOOL b);
/**
* @brief return if an space is iluminated
*
* @date 27/04/20
* @author Gonzalo Mejías
*
* @param space  
* @return bool 
*/
BOOL space_isIluminated(Space *s); 
/**
* @brief Gives information of the spaces
*
* space_print checks if it is possible to print
*
*@date 13/01/15
*@author Instructors
*
* @param pointer to the structure space
* @return status check
*/
STATUS space_print(Space* space);

#endif
