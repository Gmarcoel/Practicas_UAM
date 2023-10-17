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
#include "string.h"
#include "game.h"
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
	Game * game=NULL;
	Graphic_engine *gengine;
	T_Command command = NO_CMD;
	char LOG[WORD_SIZE]; /*Esto para el log*/
	char l[WORD_SIZE] = "-l";
	char arg[WORD_SIZE] = "";
	game=game_create();
	strcpy(LOG,"LOG");
	
	if (argc < 2){
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}


	
	
	
	if (game_create_from_file(game, argv[1]) == ERROR){fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}
	
	/*Esto tambien es para el log*/
	if(argv[2])
		strcpy(arg,argv[2]);
	
	if(strcmp(l,arg) == 0){ 

		if(argc >3)
			strcpy(LOG,argv[3]);
		
		game_set_log(game,LOG);
		/*game_set_log(&game,log_create(LOG,0));*/
		game_set_logc(game,1);
	}


	if ((gengine = graphic_engine_create()) == NULL){
		fprintf (stderr, "Error while initializing graphic engine.\n");
		game_destroy(game);
		return 1;
	}

	while ( (command != EXIT) && !game_is_over(game) ){
		graphic_engine_paint_game(gengine, game);
		command = get_user_input();
		game_update(game, command);
	}
	game_destroy(game);
	graphic_engine_destroy(gengine);
	return 0;
}
