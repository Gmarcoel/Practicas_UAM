/***
 * @brief Link functions library
 * @file link.h
 * @author Gabriela Trabajo
 * @version 1.0 
 * @date 24/03/20
 * @copyright GNU Public License
 */

#ifndef LINK_H_
#define LINK_H_

#include "types.h"

#define MAX_LINKS 500

typedef struct _Link Link;

/***
*@brief It creates a new link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@return a pointer to a new link
*/
Link *link_create();

/***
*@brief It destroys an already existing link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link that you want to destroy
*@return OK if it was destroyed correctly or ERROR if not
*/
STATUS link_destroy(Link *ln);

/***
*@brief It sets an id to the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param id New id for the link
*@return OK if it was added correctly or ERROR if not
*/
STATUS link_set_idLink(Link *ln, Id id);

/***
*@brief It sets a name to the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param name New name for the link
*@return OK if it was added correctly or ERROR if not
*/
STATUS link_set_name(Link *ln, char *name);

/***
*@brief It sets an id to the first space of the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param id First space id
*@return OK if it was added correctly or ERROR if not
*/
STATUS link_set_id1(Link *ln, Id id);

/***
*@brief It sets an id to the second space of the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param id Second space id
*@return OK if it was added correctly or ERROR if not
*/
STATUS link_set_id2(Link *ln, Id id);

/***
*@brief It sets a connection of spaces to the link (faster).
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param id1 First space id
*@param id2 Second space id
*@return OK if it was added correctly or ERROR if not
*/
STATUS link_set_connection(Link *ln, Id id1, Id id2);

/***
*@brief It sets an status to the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@param state Status of the link
*@return OK if it was changed correctly or ERROR if not
*/
STATUS link_set_status(Link *ln, CONNECTION state);

/***
*@brief It gets the id of the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@return The id of the link
*/
Id link_get_idLink(Link *ln);

/***
*@brief It gets the name of the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@return The name of the link
*/
const char *link_get_name(Link *ln);

/***
*@brief It gets the id of the first space linked.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@return The id of the first space
*/
Id link_get_id1(Link *ln);

/***
*@brief It gets the id of the second space linked.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@return The id of the second space
*/
Id link_get_id2(Link *ln);

/***
*@brief It gets the status of the link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link
*@return The status of the link
*/
CONNECTION link_get_status(Link *ln);

/***
*@brief It prints all the content of a link.
*@date 24/03/20
*@author Gabriela Trabajo de Rada
*@param ln Pointer to the link you want to print
*@return OK if it was printed correctly or ERROR if not
*/
STATUS link_print(Link *ln);

/***
*@brief It returns the other id of the link
*@date 24/03/20
*@author Javier López
*@param ln Pointer to the link
*@param id id to the space
*@return id of the linked space
*/
Id link_get_otherId(Link *ln, Id id);


#endif