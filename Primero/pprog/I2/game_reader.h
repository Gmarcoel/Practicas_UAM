/** 
 * @brief It loads the game space from a file
 * 
 * @file game_reader.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
#ifndef GAME_READER_H
#define GAME_READER_H

#include "command.h"
#include "types.h"
#include "game.h"
#include "space.h"

/***@brief Load a game from a file
*
* game_load_spaces initializes all variables inside a space
*
*@date 16/01/20
*@author Instructors
*
* @param game structure
* @param file name 
* @return status
*/
STATUS game_load_spaces(Game* game, char* filename);
STATUS game_load_objects(Game* game, char* filename);
#endif