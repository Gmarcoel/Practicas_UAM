/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Marcos Parra
 * @version 1.0 
 * @date 12-02-2020 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "graphic_engine.h"


#define MAX_NAME 256


/*Private functions*/
int game_loop_init(Game* game, Graphic_engine** gengine, char* file_name);
void game_loop_run(Game* game, Graphic_engine* gengine, char* file_name);
void game_loop_cleanup(Game* game, Graphic_engine* gengine);

/*Main program*/
int main(int argc, char* argv[]) 
{
   /*Declarations*/
   Game game;
   Graphic_engine* gengine;
   int c;
   char filename_dat[MAX_NAME] = "";
   char filename_log[MAX_NAME] = "";
 
   /*Argument checking*/
   while ((c = getopt(argc, argv, "l:")) != -1)
   {
      switch (c)
      {
         case 'l':
            if (optarg != NULL)
            {
               strcpy(filename_log, optarg);
            }
            break;

         case '?':
            fprintf(stderr, "Use: %s [-l <log_file>] <game_data_file>\n", argv[0]);
            return 1;
            break;

         default:
            break;
      }
   }
   if (optind >= argc)
   {
      fprintf(stderr, "Use: %s [-l <log_file>] <game_data_file>\n", argv[0]);
      return 1;
   }
   else
   {
      strcpy(filename_dat, argv[optind]);
   }
   
   /*Start the game*/
   /*if (!game_loop_init(&game, &gengine, argv[1]))*/
   if (!game_loop_init(&game, &gengine, filename_dat))
   {
      game_loop_run(&game, gengine, filename_log);
      game_loop_cleanup(&game, gengine);
   }
   
   /*Correct exit*/
   return 0;
}

int game_loop_init(Game* game, Graphic_engine** gengine, char* file_name)
{
   /*Game creation*/
   if (game_create_from_file(game, file_name) == ERROR) 
   {
      fprintf(stderr, "Error while initializing game.\n");
      return 1;
   }
   
   /*Graphic engine creation*/
   if ((*gengine = graphic_engine_create()) == NULL) 
   {
      fprintf(stderr, "Error while initializing graphic engine.\n");
      game_destroy(game);
      return 1;
   }

   /*Correct exit*/
   return 0;
}

void game_loop_run(Game* game, Graphic_engine* gengine, char* file_name)
{
   /*Declaration*/
   T_Command command = NO_CMD;
   extern char* cmd_to_str[N_CMD][N_CMDT];

   char cmd_args[ARGS_SIZE] = "";
   FILE* logfile = NULL;
   
   /*Open log file*/
   logfile = fopen (file_name, "w");

   /*Game execution*/
   while ((command != EXIT) && !game_is_over(game)) 
   {
      graphic_engine_paint_game(gengine, game);
      command = get_user_input(cmd_args);
      game_update(game, command, cmd_args);

      if (logfile)
      {
         fprintf(logfile, "%s %s: %s\n", cmd_to_str[command-NO_CMD][CMDL]
                                       , cmd_args
                                       , game_get_last_cmd_status(game) == OK ? "OK" : "ERROR" );
      }
   }
   
   /*Close log file*/
   if (logfile)
      fclose(logfile);
}

void game_loop_cleanup(Game* game, Graphic_engine* gengine)
{
   /*Free memory*/
   game_destroy(game);
   graphic_engine_destroy(gengine);
}

