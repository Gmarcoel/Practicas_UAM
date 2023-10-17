/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
/*** @brief checks if game is loadable
*
* main checks if it is possible to
* load the game 
*
*@date 16/01/20
*@author Instructors
*
* @param conteins the number of arguments introduced
* @param array of pointers to characters
*/
int main(int argc, char *argv[]){
	Game game;
	T_Command command = NO_CMD;
	Graphic_engine *gengine;
	
	if (argc < 2){
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}
	
	if (game_create_from_file(&game, argv[1]) == ERROR){fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}
	
	if ((gengine = graphic_engine_create()) == NULL){
		fprintf (stderr, "Error while initializing graphic engine.\n");
		game_destroy(&game);
		return 1;
	}
	
	while ( (command != EXIT) && !game_is_over(&game) ){
		graphic_engine_paint_game(gengine, &game);
		command = get_user_input();
		game_update(&game, command);
	}
	
	game_destroy(&game);
	graphic_engine_destroy(gengine);
	return 0;
}
