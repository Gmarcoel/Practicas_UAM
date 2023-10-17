/** 
 * @brief It defines a player
 * 
 * @file player.h
 * @author Guillermo Martin
 * @version 1.0 
 * @date 16/02/20
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "inventory.h"
#include "object.h"


#define MAX_PLAYERS 100
#define FIRST_PLAYER 1
/***
*
* @brief elements of a player
* Defines the ids and name of a player
*
*/
typedef struct _Player Player;

/***
* @brief It creates a new player
* player_create reserves memory for
* new player if it is created
* @date 16/02/20
* @author Guillermo Martín
* @param the identification of the player
* @return the player created
*/
Player* player_create(Id id);
/***
* @brief It destroys a player
* player_destroy deletes the player 
* and frees the memory
* @date 16/02/20
* @author Guillermo Martín
* @param existing player
* @return status check
*/
STATUS player_destroy(Player* player);
/***
* @brief Searches the id 
* player_get_id searches the id of the player
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure player
* @return the id
*/
Id player_get_id(Player* player);
/***
* @brief It changes the name
* player_set_name changes the name of the player
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure
* @param name to change
* @return status 
*/
STATUS player_set_name(Player* player, char* name);
/***
* @brief Searches the name
* player_get_name searches the name of the player
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure player
* @return the name
*/
const char* player_get_name(Player* player);

/***
* @brief It sets the player location
* player_set_name changes the position of
* north in the structure
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS player_set_location(Player* player, Id id);
/***
* @brief Searches the location value
* player_get_location searches the player location
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure player
* @return the id
*/
Id player_get_location(Player* player);
/**
* @brief It changes position
*
* player_set_name changes the position 
* of the object66
*
* @date 16/02/20
* @author Guillermo Martín
*
* @param pointer to the structure
* @param value of the id
* @return status check
*/
STATUS player_add_object(Player* player, Id value);
/**
* @brief deletes object from player inventory
*
* @date 16/02/20
* @author Guillermo Martín
*
* @param player
* @param id of the object
* @return status check
*/
STATUS player_del_object(Player* player,Id id);
/***
* @brief Searches the id object
* player_get_object searches the object id
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure player
* @return the id
*/
Id * player_get_objects(Player* player);
/**
* @brief Gives information of the players
* player_print checks if it is possible to print
* @date 16/02/20
* @author Guillermo Martín
* @param pointer to the structure player
* @return status check
*/
STATUS player_print(Player* player);
/**
*@brief Return players inventory
*
*
*@date 01/04/20
*@author Guillermo Martín
*
* @param player to the structure player
* @return inventory
*/
Inventory *player_get_inventory(Player * player);
/**
*@brief Changes player inventory
*
*
*@date 01/04/20
*@author Guillermo Martín
*
* @param player to the structure player
* @param backpach the inventory
* @return status
*/
STATUS player_set_inventory(Player * player, Inventory * backpack);
/**
*@brief Checks if player has object
*
*
*@date 01/02/20
*@author Guillermo Martín
*
* @param player to the structure player
* @param id object to be comproved
* @return status
*/
STATUS player_is_object(Player *player, Id id);


#endif