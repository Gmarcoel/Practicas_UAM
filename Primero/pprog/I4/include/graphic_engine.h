/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
/**
* 
* @brief Graphic engine structure
*
*  It defines the different elements of the graphic engine
*/
typedef struct _Graphic_engine Graphic_engine;
/**
*@brief Creates a graphic engine
*
* initializes a graphic engine
*
*@date 15/01/2019
*@author: Instructors
*

* @return a graphic engine pointer to the new initialized graphic engine
*/
Graphic_engine* graphic_engine_create();
/**
*@brief Destroys a graphic engine
*
* Destroys the send graphic engine and frees the memory
*
*@date 15/01/2019
*@author: Instructors
*
* @param graphic engine requested to be destroyed
*/
void graphic_engine_destroy(Graphic_engine *ge);
/**
*@brief Draws the game
*
* Uses the graphic engine parameters to paint the game board
*
*@date 15/01/2019
*@author: Instructors
*
* @param graphic engine used to paint the game
* @return the price in Euro of the input coffee
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
/**
*@brief Print th command in screen
*
* Receive a command and out it into the screen
*
*@date 15/01/2019
*@author: Instructors
*
* @param graphic engine used to paint the game
* @param char engine used to paint the game
* @return the price in Euro of the input coffee
*/
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
