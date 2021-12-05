/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_reader.h"

#define N_CALLBACK 9

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/
void game_callback_unknown(Game *game);
void game_callback_exit(Game *game);
void game_callback_next(Game *game);
void game_callback_back(Game *game);
void game_callback_take(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_left(Game *game);
void game_callback_right(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_left,
    game_callback_right};

/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

STATUS game_create(Game *game)
{
  int i;

  for (i = 0; i <= MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->last_cmd = NO_CMD;
  game->player = player_create(1);
  game->die = die_create(1);
  strcpy(game->log,"LOG");
  game->logc= 0;

  for (i = 0; i <= MAX_OBJECT; i++)
  {
    game->objects[i] = NULL;
  }

  return OK;
}

STATUS game_create_from_file(Game *game, char *filename)
{

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename) == ERROR)
    return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));
  /*game_set_object_location(game, game_get_space_id_at(game, 0));*/

  return OK;
}

STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
  }
  player_destroy(game->player);

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    object_destroy(game->objects[i]);
  }

  die_destroy(game->die);

  return OK;
}

STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (space == NULL || game == NULL)
  {
    return ERROR;
  }

  while (game->spaces[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

STATUS game_add_object(Game *game, Object *object)
{
  int i = 0;

  if (object == NULL || game == NULL)
  {
    return ERROR;
  }

  while (game->objects[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_OBJECT)
  {
    return ERROR;
  }

  game->objects[i] = object;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Object *game_get_object(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; game->objects != NULL; i++)
  {
    if (id == object_get_id(game->objects[i]))
    {
      return game->objects[i];
    }
  }

  return NULL;
}



STATUS game_set_player_location(Game *game, Id id)
{

  if (!game)
  {
    return ERROR;
  }

  player_set_location(game->player, id);
  return OK;
}


/*NO SE QUE HACER AQUI LO SIENTO YO DEL FUTURO LO SIENTO MUCHO EN SERIO*/
STATUS game_set_object_location(Game *game, Id id, Id id_object)
{

  int i = 0;
  if (id == NO_ID)
  {
    return ERROR;
  }
  for (i = 0; i <= MAX_SPACES; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      space_add_object(game->spaces[i], id_object);
      return OK;
    }
  }
  return ERROR;
}

Id game_get_player_location(Game *game)
{
  return player_get_location(game->player);
}

Id game_get_object_location(Game *game, Id id_object)
{
  int i;
  if (!game)
    return NO_ID;
  for (i = 0; game->spaces[i]!=NULL; i++)
  {
    if (space_is_object(game->spaces[i], id_object) == OK)
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

STATUS game_update(Game *game, T_Command cmd)
{
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  /*printf("=> Object location: %d\n", (int) object_print(game->object));*/
  printf("=> Player location: %d\n", (int)player_print(game->player));
  printf("prompt:> ");
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}


/*
  LOG a ver si esta implementacion funciona
*/

void game_log(Game * game, const char * log)
{
  if (game->logc == 1)
  {
  FILE * f = NULL;
  f = fopen(game->log,"a");
  fprintf(f,"%s",log);
  fclose(f);
  return;
  }
}

/**
   Callbacks implementation for each action 
*/

void game_callback_unknown(Game *game)
{
  game_log(game,"\nunknown: OK");
}

void game_callback_exit(Game *game)
{
  game_log(game,"\nexit: OK");
}

void game_callback_next(Game *game)
{
  const char e[WORD_SIZE] = "\nnext: ERROR";
  const char o[WORD_SIZE] = "\nnext: OK";
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game,e);
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      game_log(game,o);
      return;
    }
  }
  game_log(game,e);
}

void game_callback_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    game_log(game,"\nback: ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      /*  log_write(game->log,"\nback: OK");  */
      return;
    }
  }
  /*  log_write(game->log,"\nback: ERROR"); */
}

void game_callback_take(Game *game)
{
  Space *space;
  char name[WORD_SIZE] = "";
  Id object = NO_ID;
  int i;

  scanf("%s", name);
  if (strcmp(name, "") == 0)
  {
        game_log(game,"\ntake: ERROR");
    printf("No object selected");
    return;
  }

  if(player_get_object(game->player)!=NO_ID)
    return;

  space = game_get_space(game, game_get_player_location(game));


  /*Encuentra objeto dentro del juego*/
  for (i = 0; game->objects[i] != NULL; i++)
  {
    if (strcmp(object_get_name(game->objects[i]), name) == 0)
      object = object_get_id(game->objects[i]);
  }

  /*Si objeto no existe*/
  if (object == NO_ID)
  {
            game_log(game,"\ntake: ERROR");
    fprintf(stdout, "Object chosen does not exist in game");
    return;
  }

  /*Comprueba que objeto esta en espacio*/
  if (space_is_object(space, object) == OK)
  {
    player_set_object(game->player, object);
    space_del_object(space, object);
            game_log(game,"\ntake: OK");
  } else {
            game_log(game,"\ntake: ERROR");
    printf("Object is not in this space");
  }  
          game_log(game,"\ntake: ERROR");
  return;
}

void game_callback_drop(Game *game)
{
  Space *s;
  s = game_get_space(game, game_get_player_location(game));
  if (player_get_object(game->player) == NO_ID)
  {
    fprintf(stdout, "You don't have any object");
            game_log(game,"\ndrop: ERROR");
    return;
  }
  space_add_object(s, player_get_object(game->player));
  player_set_object(game->player, NO_ID);
  game_log(game,"\ndrop: OK");
  return;
}

void game_callback_roll(Game *game)
{
  die_roll(game->die);
  game_log(game,"\nroll: OK");
}

void game_callback_left(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game,"\nleft: ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      game_log(game,"\nleft: OK");
      return;
    }
  }
}

void game_callback_right(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game,"\nright: ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game_log(game,"\nright: ERROR");
      }
     game_log(game,"\nright: OK");
      return;
    }
  }
}
