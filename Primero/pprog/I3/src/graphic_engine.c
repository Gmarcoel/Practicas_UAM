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
#include "object.h"

#define LENGHT 4

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

  ge->map = screen_area_init(1, 1, 48, /*13*/ 21);
  ge->descript = screen_area_init(50, 1 /*9*/, 29, 21 /*13*/);
  ge->banner = screen_area_init(28, /*15*/ 23, 23, 1);
  ge->help = screen_area_init(1, /*16*/ 23, 78, 2);
  ge->feedback = screen_area_init(1, /*19*/ 27, 78, 3);

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
  int i = 0, j = 0;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID,id_east = NO_ID,id_west = NO_ID;
  Space *space_act = NULL,*space_back = NULL,*space_next = NULL;
  char obj[LENGHT][MAX_OBJECT];
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char *name;
  Id *id;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = link_get_otherId(game_get_link(game, space_get_linkNorth(space_act)), id_act);
    id_next = link_get_otherId(game_get_link(game, space_get_linkSouth(space_act)), id_act);
    space_back = game_get_space(game, id_back);
    space_next = game_get_space(game, id_next);
  }

  for (i = 0; game_get_object_i(game, i) != NULL; i++)
  {
    strcpy(obj[i], "  ");
    if (game_get_object_location(game, object_get_id(game_get_object_i(game, i))) == id_back)
    {
      strcpy(obj[j], object_get_name(game_get_object_i(game, i)));
      j++;
    }
  }

  if (id_back != NO_ID)
  {
    id_east = link_get_otherId(game_get_link(game, space_get_linkEast(space_back)), id_back);
    id_west = link_get_otherId(game_get_link(game, space_get_linkWest(space_back)), id_back);
    if(space_get_linkWest(space_back)!=NO_ID)
    {
      sprintf(str, "       |         %2d| --> %2d", (int)id_back,(int)id_west);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |  %ld", space_get_icon(game_get_space(game, id_back)),space_get_linkWest(space_back));
    } else if (space_get_linkEast(space_back)!=NO_ID) {
      sprintf(str, " %2d <--|         %2d|",(int)id_east, (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "    %ld |  %s  |",space_get_linkEast(space_back),space_get_icon(game_get_space(game, id_back)));
    } else {
      sprintf(str, "       |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |", space_get_icon(game_get_space(game, id_back)));
    }


    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon2(game_get_space(game, id_back)));
    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon3(game_get_space(game, id_back)));
    screen_area_puts(ge->map, str);

    sprintf(str, "       |%s %s %s %s|", obj[0], obj[1], obj[2], obj[3]);
    screen_area_puts(ge->map, str);

    sprintf(str, "       +-----------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "             ^ %ld",space_get_linkNorth(space_act));
    screen_area_puts(ge->map, str);
  }

  j = 0;

  for (i = 0; game_get_object_i(game, i) != NULL; i++)
  {
    strcpy(obj[i], "  ");
    if (game_get_object_location(game, object_get_id(game_get_object_i(game, i))) == id_act)
    {
      strcpy(obj[j], object_get_name(game_get_object_i(game, i)));
      j++;
    }
  }

  if (id_act != NO_ID)
  {
    sprintf(str, "       +-----------+");
    screen_area_puts(ge->map, str);
    id_east = link_get_otherId(game_get_link(game, space_get_linkEast(space_act)), id_act);
    id_west = link_get_otherId(game_get_link(game, space_get_linkWest(space_act)), id_act);
    if(space_get_linkWest(space_act)!=NO_ID)
    {
      sprintf(str, "       | ;D      %2d| --> %2d", (int)id_act,(int)id_west);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |  %ld", space_get_icon(game_get_space(game, id_act)),space_get_linkWest(space_act));
    } else if (space_get_linkEast(space_act)!=NO_ID) {
      sprintf(str, " %2d <--| D:      %2d|",(int)id_east, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "    %ld |  %s  |",space_get_linkEast(space_act),space_get_icon(game_get_space(game, id_act)));
    } else {
      sprintf(str, "       | :D      %2d|", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |", space_get_icon(game_get_space(game, id_act)));
    }
    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon2(game_get_space(game, id_act)));
    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon3(game_get_space(game, id_act)));
    screen_area_puts(ge->map, str);

    sprintf(str, "       |%s %s %s %s|", obj[0], obj[1], obj[2], obj[3]);
    screen_area_puts(ge->map, str);
    sprintf(str, "       +-----------+");
    screen_area_puts(ge->map, str);
  }

  j = 0;

  for (i = 0; game_get_object_i(game, i) != NULL; i++)
  {
    strcpy(obj[i], "  ");
    if (game_get_object_location(game, object_get_id(game_get_object_i(game, i))) == id_next)
    {
      strcpy(obj[j], object_get_name(game_get_object_i(game, i)));
      j++;
    }
  }

  if (id_next != NO_ID)
  {
    sprintf(str, "             v %ld", space_get_linkSouth(space_act));
    screen_area_puts(ge->map, str);
    sprintf(str, "       +-----------+");
    screen_area_puts(ge->map, str);
    id_east = link_get_otherId(game_get_link(game, space_get_linkEast(space_next)), id_next);
    id_west = link_get_otherId(game_get_link(game, space_get_linkWest(space_next)), id_next);
    if(space_get_linkWest(space_next)!=NO_ID)
    {
      sprintf(str, "       |         %2d| --> %2d", (int)id_next,(int)id_west);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |  %ld", space_get_icon(game_get_space(game, id_next)),space_get_linkWest(space_next));
    } else if (space_get_linkEast(space_next)!=NO_ID) {
      sprintf(str, " %2d <--|         %2d|",(int)id_east, (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "    %ld |  %s  |",space_get_linkEast(space_next),space_get_icon(game_get_space(game, id_next)));
    } else {
      sprintf(str, "       |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "       |  %s  |", space_get_icon(game_get_space(game, id_next)));
    }
    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon2(game_get_space(game, id_next)));
    screen_area_puts(ge->map, str);
    sprintf(str, "       |  %s  |", space_get_icon3(game_get_space(game, id_next)));
    screen_area_puts(ge->map, str);

    sprintf(str, "       |%s %s %s %s|", obj[0], obj[1], obj[2], obj[3]);
    screen_area_puts(ge->map, str);
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);

  screen_area_puts(ge->descript, "  Objects location");
  for (i = 0; game_get_object_i(game, i) != NULL; i++)
  {
    obj_loc = game_get_object_location(game, object_get_id(game_get_object_i(game, i)));
    if (obj_loc != NO_ID)
    {
      sprintf(str, "  %s: %d", object_get_name(game_get_object_i(game, i)), (int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }
  /*Implementar el inventario*/
  screen_area_puts(ge->descript, "");
  sprintf(str, "  Player location: %ld", game_get_player_location(game));
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Player objects: ");
  screen_area_puts(ge->descript, str);

  id = inventory_get_objects(player_get_inventory(game_get_player_i(game, 0)));                    /*Id tiene todos los obj del inv*/
  for (i = 0; i < inventory_get_NumObjects(player_get_inventory(game_get_player_i(game, 0))); i++) /*pasa por cada objeto del inv*/
  {
    name = object_get_name(game_get_object(game, id[i])); /*coge nombre objeto*/
    if (id[i] != NO_ID && name != NULL)                   /*si */
    {
      sprintf(str, "  %s", name);
      screen_area_puts(ge->descript, str);
    }
  }
  sprintf(str, "  Last die value: %i", die_last_value(game_get_die(game)));
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Description: %s", game_get_description(game));
  screen_area_puts(ge->descript, str);

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " next or n, back or b, exit or e, take or t, drop or d, left or l, right or r, roll or rl");
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
