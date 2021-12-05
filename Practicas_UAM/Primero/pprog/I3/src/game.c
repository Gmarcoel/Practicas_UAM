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

#define N_CALLBACK 12
/*
* 
* @brief The Game structure
*
* It stores information of the different parts of the game
*/
struct _Game
{
  Player *players[MAX_OBJECT + 1]; /*Game players*/
  Object *objects[MAX_OBJECT + 1]; /*Objects used in the game*/
  Space *spaces[MAX_SPACES + 1];   /*Spaces where the players move*/
  Link *links[MAX_LINKS + 1];
  T_Command last_cmd; /*Last command input */
  Die *die;
  char log[WORD_SIZE];
  int logc;
  char description[WORD_SIZE];
};
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
void game_callback_inspect(Game *game);
void game_callback_move(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_left,
    game_callback_right,
    game_callback_inspect,
    game_callback_move};

/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

Game *game_create()
{
  int i;
  Game *newGame = NULL;

  newGame = (Game *)malloc(sizeof(Game));

  for (i = 0; i <= MAX_SPACES; i++)
  {
    newGame->spaces[i] = NULL;
  }

  newGame->last_cmd = NO_CMD;

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    newGame->players[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    newGame->links[i] = NULL;
  }

  newGame->die = die_create(1);
  strcpy(newGame->log, "LOG");
  newGame->logc = 0;

  for (i = 0; i <= MAX_OBJECT; i++)
  {
    newGame->objects[i] = NULL;
  }

  strcpy(newGame->description, "");

  return newGame;
}

STATUS game_create_from_file(Game *game, char *filename)
{

  /*
  if (game_create(game) == ERROR)
    return ERROR;
  */

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename) == ERROR)
    return ERROR;

  if (game_load_players(game, filename) == ERROR)
    return ERROR;

  if (game_load_links(game, filename) == ERROR)
    return ERROR;

  /*game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));*/

  return OK;
}

STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
  }
  for (i = 0; game->players[i] != NULL; i++)
  {
    player_destroy(game->players[i]);
  }
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    object_destroy(game->objects[i]);
  }
  for (i = 0; game->links[i] != NULL; i++)
  {
    link_destroy(game->links[i]);
  }
  die_destroy(game->die);
  free(game);
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

STATUS game_add_player(Game *game, Player *player)
{
  int i = 0;
  /*añadir inicializacion del inventario*/
  if (player == NULL || game == NULL)
  {
    return ERROR;
  }

  while (game->players[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_PLAYERS)
  {
    return ERROR;
  }

  game->players[i] = player;

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

STATUS game_add_link(Game *game, Link *link)
{
  int i = 0;

  if (link == NULL || game == NULL)
  {
    return ERROR;
  }

  while (game->links[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_LINKS)
  {
    return ERROR;
  }

  game->links[i] = link;

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

  player_set_location(game->players[0], id);
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
  return player_get_location(game->players[0]);
}

Id game_get_object_location(Game *game, Id id_object)
{
  int i;
  if (!game)
    return NO_ID;
  for (i = 0; game->spaces[i] != NULL; i++)
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
  printf("=> Player location: %d\n", (int)player_print(game->players[0]));
  printf("prompt:> ");
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

/*funciones de descripciones*/
STATUS game_set_description(Game *game, char *description)
{
  if (!game)
    return ERROR;
  strcpy(game->description, description);
  return OK;
}
char *game_get_description(Game *game)
{
  if (!game)
    return NULL;
  return game->description;
}
/*Funcion agggquerosa de los objetos*/
Object **game_get_objects(Game *game)
{
  if (!game)
    return NULL;
  return game->objects;
}
Object *game_get_object_i(Game *game, int i)
{
  if (!game)
    return NULL;
  return game->objects[i];
}

Player **game_get_players(Game *game)
{
  if (!game)
    return NULL;
  return game->players;
}
Player *game_get_player_i(Game *game, int i)
{
  if (!game)
    return NULL;
  return game->players[i];
}
Die *game_get_die(Game *game)
{
  if (!game)
    return NULL;
  return game->die;
}

Space **game_get_spaces(Game *game)
{
  if (!game)
    return NULL;
  return game->spaces;
}

/*
  LOG a ver si esta implementacion funciona
*/

void game_log(Game *game, const char *log)
{
  if (game->logc == 1)
  {
    FILE *f = NULL;
    f = fopen(game->log, "a");
    fprintf(f, "%s", log);
    fclose(f);
    return;
  }
}

/*Para los logs*/
char *game_get_log(Game *game)
{
  if (!game)
    return NULL;
  return game->log;
}
int game_get_logc(Game *game)
{
  if (!game)
    return NO_ID;
  return game->logc;
}

STATUS game_set_log(Game *game, char *log)
{
  if (!game)
    return ERROR;
  strcpy(game->log, log);
  return OK;
}
STATUS game_set_logc(Game *game, int logc)
{
  if (!game)
    return ERROR;
  game->logc = logc;
  return OK;
}

/*Poderoso game get link*/
Link *game_get_link(Game *game, Id id)
{
  int i;
  if (!game)
    return NULL;
  for (i = 0; game->links != NULL; i++)
  {
    if (link_get_idLink(game->links[i]) == id)
      return game->links[i];
  }
  return NULL;
}

/**
   Callbacks implementation for each action 
*/

void game_callback_unknown(Game *game)
{
  game_log(game, "\nunknown: OK");
}

void game_callback_exit(Game *game)
{
  game_log(game, "\nexit: OK");
}
/*NEXT*/
void game_callback_next(Game *game)
{
  const char e[WORD_SIZE] = "\nnext: ERROR";
  const char o[WORD_SIZE] = "\nnext: OK";
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  /*Location del player*/
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game, e);
    return;
  }
  /*Mover el player*/
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = link_get_otherId(game_get_link(game, space_get_linkSouth(game->spaces[i])), current_id); /*space_get_south(game->spaces[i]);*/
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      game_log(game, o);
      return;
    }
  }
  game_log(game, e);
}

void game_callback_back(Game *game)
{
  const char e[WORD_SIZE] = "\nnext: ERROR";
  const char o[WORD_SIZE] = "\nnext: OK";
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game, e);
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = link_get_otherId(game_get_link(game, space_get_linkNorth(game->spaces[i])), current_id); /*space_get_north(game->spaces[i]);*/
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      game_log(game, o);
      return;
    }
  }
  game_log(game, e);
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
    game_log(game, "\ntake: ERROR No object selected");
    printf("No object selected");
    return;
  }

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
    game_log(game, "\ntake: ERROR Object chosen does not exist in game");
    fprintf(stdout, "Object chosen does not exist in game");
    return;
  }

  /*Comprueba que objeto esta en espacio*/
  if (space_is_object(space, object) == OK)
  {
    if (player_add_object(game->players[0], object) == ERROR)
    {
      game_log(game, "\ntake: ERROR The backpack is full");
      fprintf(stdout, "The backpack is full");
      return;
    }
    space_del_object(space, object);
    game_log(game, "\ntake: OK");
    return;
  }
  else
  {
    game_log(game, "\ntake: ERROR Object is not in this space");
    printf("Object is not in this space");
    return;
  }
  game_log(game, "\ntake: ERROR reaching ending");
  return;
}

void game_callback_drop(Game *game)
{
  /*Space *s;
  s = game_get_space(game, game_get_player_location(game));
  if (player_get_object(game->players[0]) == NO_ID)
  {
    fprintf(stdout, "You don't have any object");
            game_log(game,"\ndrop: ERROR");
    return;
  }
  space_add_object(s, player_get_object(game->players[0]));
  player_set_object(game->players[0], NO_ID);
  game_log(game,"\ndrop: OK");
  return;*/

  Space *space;
  char name[WORD_SIZE] = "";
  Id object = NO_ID;
  int i;

  scanf("%s", name);
  if (strcmp(name, "") == 0)
  {
    game_log(game, "\ndrop: ERROR");
    printf("No object selected");
    return;
  }

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
    game_log(game, "\ndrop: ERROR Object chosen does not exist in game");
    fprintf(stdout, "Object chosen does not exist in game");
    return;
  }

  /*Comprueba que objeto esta en la mochila*/
  if (player_is_object(game->players[0], object) == OK)
  {
    if (space_add_object(space, object) == ERROR)
    {
      game_log(game, "\ndrop: ERROR The backpack is full");
      fprintf(stdout, "The backpack is full");
      return;
    }
    player_del_object(game->players[0], object);
    game_log(game, "\ndrop: OK");
    return;
  }
  else
  {
    game_log(game, "\ndrop: ERROR Object is not in the backpack");
    printf("Object is not in the backpack");
    return;
  }
  game_log(game, "\ndrop: ERROR");
  return;
}

void game_callback_roll(Game *game)
{
  die_roll(game->die);
  game_log(game, "\nroll: OK");
}

void game_callback_left(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_log(game, "\nleft: ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = link_get_otherId(game_get_link(game, space_get_linkEast(game->spaces[i])), current_id); /*current_id = space_get_east(game->spaces[i]);*/
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      game_log(game, "\nleft: OK");
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
    game_log(game, "\nright: ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = link_get_otherId(game_get_link(game, space_get_linkWest(game->spaces[i])), current_id);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game_log(game, "\nright: OK");
        return;
      }
      game_log(game, "\nright: ERROR");
      return;
    }
  }
}

void game_callback_inspect(Game *game)
{
  Space *space;
  char name[WORD_SIZE] = "";
  Id object = NO_ID;
  int i;

  scanf("%s", name);
  if (strcmp(name, "") == 0)
  {
    game_log(game, "\ntake: ERROR");
    printf("No object selected");
    return;
  }

  space = game_get_space(game, game_get_player_location(game));

  if (strcmp(name, "s") == 0 || strcmp(name, "space") == 0)
  {
    /*Estoy hay que printearlo en la interfaz*/
    strcpy(game->description, space_get_description(space));
  }
  else
  {
    /*Encuentra objeto dentro del juego*/
    for (i = 0; game->objects[i] != NULL; i++)
    {
      if (strcmp(object_get_name(game->objects[i]), name) == 0)
        object = object_get_id(game->objects[i]);
    }

    /*Si objeto no existe*/
    if (object == NO_ID)
    {
      game_log(game, "\ninspect: ERROR");
      fprintf(stdout, "Object chosen does not exist in game");
      return;
    }

    /*Comprueba que objeto esta en espacio(tambien ha que comprobar que este en la mochila)*/
    if (space_is_object(space, object) == OK || inventory_is_object(player_get_inventory(game->players[0]), object) == OK)
    {
      /*Estoy hay que printearlo en la interfaz*/
      strcpy(game->description, object_get_description(game_get_object(game, object)));
      game_log(game, "\ninspect: OK");
      return;
    }
    else
    {
      game_log(game, "\ninspect: ERROR");
      printf("Object is not in this space");
      return;
    }
    game_log(game, "\ninspect: ERROR");
  }
  return;
}

void game_callback_move(Game *game)
{
  char move[WORD_SIZE] = "";
  scanf("%s", move);
  if (strcmp(move, "") == 0)
  {
    game_log(game, "\nmove: ERROR No movement selected");
    printf("No movement selected");
    return;
  }
  if (strcmp(move, "south")==0 || strcmp(move, "s")==0)
  {
    game_callback_next(game);
    game_log(game, "\nmove: OK");
    return;
  }
  if (strcmp(move, "north")==0 || strcmp(move, "n")==0)
  {
    game_callback_back(game);
    game_log(game, "\nmove: OK");
    return;
  }
  if (strcmp(move, "east")==0 || strcmp(move, "e")==0)
  {
    game_callback_right(game);
    game_log(game, "\nmove: OK");
    return;
  }
  if (strcmp(move, "west")==0 || strcmp(move, "w")==0)
  {
    game_callback_left(game);
    game_log(game, "\nmove: OK");
    return;
  }

  game_log(game, "\nmove: ERROR unknown move");
  printf("Unknown move");
  return;
}