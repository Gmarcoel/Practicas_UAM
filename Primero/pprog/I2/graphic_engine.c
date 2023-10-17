/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"
#include "command.h"
#include "string.h"

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));

  ge->map = screen_area_init(1, 1, 48, /*13*/21);
  ge->descript = screen_area_init(50, /*1*/9, 29, 13);
  ge->banner = screen_area_init(28, /*15*/23, 23, 1);
  ge->help = screen_area_init(1, /*16*/23, 78, 2);
  ge->feedback = screen_area_init(1, /*19*/27, 78, 3);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  int i;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj[WORD_SIZE];
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  obj[0] = '\0';

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
  }


  for (i = 0; game->objects[i] != NULL; i++)
  {
    if (game_get_object_location(game, object_get_id(game->objects[i])) == id_back){
      strcpy(obj,object_get_name(game->objects[i]));
      break;
    } else {
      strcpy(obj,"  ");
    }
  }

  if (id_back != NO_ID)
  {
    sprintf(str, "  |         %2d|", (int)id_back);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |     %s    |", obj);
    screen_area_puts(ge->map, str);

    
    sprintf(str, "  |  %s  |", space_get_icon(game_get_space(game,id_back)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon2(game_get_space(game,id_back)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon3(game_get_space(game,id_back)));
    screen_area_puts(ge->map, str);
    

    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "        ^");
    screen_area_puts(ge->map, str);
  }

  for (i = 0; game->objects[i] != NULL; i++)
  {
    if (game_get_object_location(game, object_get_id(game->objects[i])) == id_act){
      strcpy(obj,object_get_name(game->objects[i]));
      break;
    } else {
      strcpy(obj,"  ");
    }
  }

  if (id_act != NO_ID)
  {
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "  | 8D      %2d|", (int)id_act);
    screen_area_puts(ge->map, str);

    sprintf(str, "  |  %s  |", space_get_icon(game_get_space(game,id_act)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon2(game_get_space(game,id_act)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon3(game_get_space(game,id_act)));
    screen_area_puts(ge->map, str);    

    sprintf(str, "  |     %s    |", obj);
    screen_area_puts(ge->map, str);
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);
  }

  for (i = 0; game->objects[i] != NULL; i++)
  {
    if (game_get_object_location(game, object_get_id(game->objects[i])) == id_next){
      strcpy(obj,object_get_name(game->objects[i]));
      break;
    } else {
      strcpy(obj,"  ");
    }
  }

  if (id_next != NO_ID)
  {
    sprintf(str, "        v");
    screen_area_puts(ge->map, str);
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "  |         %2d|", (int)id_next);
    screen_area_puts(ge->map, str);    

    sprintf(str, "  |  %s  |", space_get_icon(game_get_space(game,id_next)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon2(game_get_space(game,id_next)));
    screen_area_puts(ge->map, str);
    sprintf(str, "  |  %s  |", space_get_icon3(game_get_space(game,id_next)));
    screen_area_puts(ge->map, str);


    sprintf(str, "  |     %s    |", obj);
    screen_area_puts(ge->map, str);
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);

  screen_area_puts(ge->descript, "  Objects location");
  for (i = 0; game->objects[i] != NULL; i++)
  {
    obj_loc = game_get_object_location(game, object_get_id(game->objects[i]));
    if (obj_loc != NO_ID)
    {
      sprintf(str, "  %s: %d", object_get_name(game->objects[i]), (int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }
    screen_area_puts(ge->descript, "");
    sprintf(str,"  Player object: %s",object_get_name(game_get_object(game,player_get_object(game->player))));
      screen_area_puts(ge->descript, str);
    sprintf(str,"  Last die value: %i",die_last_value(game->die));
      screen_area_puts(ge->descript, str);



  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " next or n, back or b, exit or e, take or t, drop or d, left or l, roght or r, roll or rl");
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
