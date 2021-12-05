/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H


#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"
#include "link.h"

typedef struct _Game Game;
/***@brief Initialize game
*
* game_create initializes all the variables inside a game
*
*@date 15/01/2019
*@author: Instructors
*
* @param game intended to be initialized
* @return a Status check
*/
Game* game_create();
/***@brief Load a game from a file
*
* game_create_from_file initializes a game from a saved file
*
*@date 15/01/2019
*@author: Instructors
*
* @param game intended to be initialized
* @param file name
* @return a Status check
*/
STATUS game_create_from_file(Game* game, char* filename);
/***@brief Updates the game
*
* game_update updates the game with the last command
*
*@date 15/01/2019
*@author: Instructors
*
* @param game 
* @param command used
* @return a Status check
*/
STATUS game_update(Game* game, T_Command cmd);
/***@brief Eliminates a game
*
* game_destroy calls other functions to free the used memory
*
*@date 14/02/20
*@author: Guillermo Martín
*
* @param game intended to be eliminated
* @return a Status check
*/
STATUS game_destroy(Game* game);
/***@brief Indicates if a game is over
*
* game_is_over checks if the game is over
*
*@date 15/01/2019
*@author: Instructors
*
* @param game
* @return a BOOL state
*/
BOOL   game_is_over(Game* game);
/*Unknown function*/
void   game_print_screen(Game* game);
/***@brief Prints player and object location and spaces
*
* game_print_data show the player and object location and spaces
*
*@date 15/01/2019
*@author: Instructors
*
* @param game 
* @return printed data
*/
void   game_print_data(Game* game);
/***@brief Returns space asked
*
* game_get_space returns the space pointer of the given id
*
*@date 15/01/2019
*@author: Instructors
*
* @param game
* @param space id
* @return the space pointer
*/
Space* game_get_space(Game* game, Id id);
/***@brief shows player location
*
* game_get_player_location calls other functions to return the player location
*
*@date 11/02/2019
*@author: Guillermo Martín
*
* @param game
* @return a player location
*/
Id     game_get_player_location(Game* game);
/***@brief shows object location
*
* game_get_player_location calls other functions to return the object location
*
*@date 11/02/2019
*@author: Guillermo Martín
*
* @param game 
* @return object location id
*/
Id game_get_object_location(Game* game,Id id_object);

/***@brief gets last input command
*
* game_get_last_command receives a game and sends the last command used
*
*@date 15/02/2019
*@author: Instructors
*
* @param game intended to bi initialized
* @param file name
* @return a Status check
*/
T_Command game_get_last_command(Game* game);
/***@brief Adds an space
*
* game_add_space initializes a new space
*
*@date 15/01/2019
*@author: Instructors
*
* @param game where the space is going to be initialized
* @param new space
* @return a Status check
*/
STATUS game_add_space(Game* game, Space* space);
/***@brief Changes the player location
*
* game_set_player_location changes player location with a new one
*
*@date 11/02/20
*@author: Guillermo Martín
*
* @param game
* @param new location id
* @return status
*/
STATUS game_set_player_location(Game* game, Id id);
/**
* @brief Changes the player location
*
* game_set_player_location changes player location with a new one
*
* @date 11/02/20
* @author: Guillermo Martín
*
* @param game
* @param new location id
* @return status
*/
STATUS game_set_object_location(Game* game, Id id,Id id_object);
/**
* @brief get object pointer
*
* @date 11/02/20
* @author: Guillermo Martín
*
* @param game
* @param id object id
* @return object pointer
*/
Object* game_get_object(Game* game, Id id);
/**
* @brief add object to game
* @date 11/02/20
* @author: Guillermo Martín
*
* @param game
* @param object 
* @return status check
*/
STATUS game_add_object(Game* game, Object* object);
/**
* @brief add player to game
* @date 11/02/20
* @author: Guillermo Martín
*
* @param game
* @param player
* @return status check
*/
STATUS game_add_player(Game* game, Player* player);
/**
* @brief add link to game
* @date 11/02/20
* @author: Guillermo Martín
*
* @param game
* @param link
* @return status check
*/
STATUS game_add_link(Game *game, Link *link);
/*Para las descripciones*/

/**
* @brief set description
* @date 11/03/20
* @author: Javier López
*
* @param game
* @param description
* @return status check
*/
STATUS game_set_description(Game * game,char * description);
/**
* @brief get description
* @date 11/03/20
* @author: Javier López
*
* @param game
* @return description
*/
char * game_get_description(Game * game);
/*Para los logs*/

/**
* @brief get log
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return log
*/
char * game_get_log(Game * game);
/**
* @brief get log check
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return log check
*/
int game_get_logc(Game * game);
/**
* @brief set log
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @param log
* @return status check
*/
STATUS game_set_log(Game * game, char * log);
/**
* @brief set log check
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @param logc int check
* @return status check
*/
STATUS game_set_logc(Game * game, int logc);

/*Awful functions*/

/**
* @brief return game's object array
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return object ** array
*/
Object ** game_get_objects(Game * game);
/**
* @brief return game's object i
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @param i object number i
* @return object
*/
Object * game_get_object_i(Game * game, int i);
/**
* @brief return game's player array
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return player ** array
*/
Player ** game_get_players(Game * game);
/**
* @brief return game's player i
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @param i player number i
* @return player
*/
Player * game_get_player_i(Game * game, int i);
/**
* @brief return game's spaces array
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return space ** array
*/
Space ** game_get_spaces(Game * game);
/**
* @brief return game's space i
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @param i space number i
* @return space
*/
Space * game_get_space_i(Game * game, int i);
/**
* @brief return game's die
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return die
*/
Die * game_get_die(Game * game);
/**
* @brief return game's link
* @date 11/03/20
* @author: Guillermo Martín
*
* @param game
* @return link
*/
Link * game_get_link(Game * game, Id id);

#endif
