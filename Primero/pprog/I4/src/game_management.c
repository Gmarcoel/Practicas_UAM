/** 
 * @brief It loads the game space from a file
 * 
 * @file game_managemnet.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"
#include "game_management.h"

STATUS game_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char description2[WORD_SIZE] = "";
  char icon[WORD_SIZE] = "";
  char icon2[WORD_SIZE] = "";
  char icon3[WORD_SIZE] = "";
  char *toks = NULL;
  BOOL iluminated;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
  Space *space = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      iluminated = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      strcpy(description2, toks);
      toks = strtok(NULL, "|");
      strcpy(icon, toks);
      toks = strtok(NULL, "|");
      strcpy(icon2, toks);
      toks = strtok(NULL, "|");
      strcpy(icon3, toks);
      toks = strtok(NULL, "|");
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%d|%s|%s\n", id, name, north, east, south, west, up, down, iluminated, description, description2);
#endif
      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_description(space, description);
        space_set_description2(space, description2);
        space_setIlumination(space, iluminated);
        space_set_icon(space, icon);
        space_set_icon2(space, icon2);
        space_set_icon3(space, icon3);
        space_set_linkNorth(space, north);
        space_set_linkEast(space, east);
        space_set_linkSouth(space, south);
        space_set_linkWest(space, west);
        space_set_linkWest(space, west);
        space_set_linkUp(space, up);
        space_set_linkDown(space, down);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}
/*SAVE SPACES*/
STATUS game_save_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char description2[WORD_SIZE] = "";
  char icon[WORD_SIZE] = "";
  char icon2[WORD_SIZE] = "";
  char icon3[WORD_SIZE] = "";
  BOOL iluminated;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
  Space *space = NULL;
  int i;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "w");
  if (file == NULL)
  {
    return ERROR;
  }

  for (i = 0; game_get_space_i(game, i) != NULL; i++)
  {
    space = game_get_space_i(game, i);
    if (space != NULL)
    {
      id = space_get_id(space);
      strcpy(name, space_get_name(space));
      strcpy(description, space_get_description(space));
      strcpy(description2, space_get_description2(space));
      iluminated = space_isIluminated(space);
      strcpy(icon, space_get_icon(space));
      strcpy(icon2, space_get_icon2(space));
      strcpy(icon3, space_get_icon3(space));
      north = space_get_linkNorth(space);
      east = space_get_linkEast(space);
      south = space_get_linkSouth(space);
      west = space_get_linkWest(space);
      up = space_get_linkUp(space);
      down = space_get_linkDown(space);
    }
    fprintf(file, "#s:");
    fprintf(file, "%ld", id);
    fprintf(file, "|");
    fprintf(file, "%s", name);
    fprintf(file, "|");
    fprintf(file, "%ld", north);
    fprintf(file, "|");
    fprintf(file, "%ld", east);
    fprintf(file, "|");
    fprintf(file, "%ld", south);
    fprintf(file, "|");
    fprintf(file, "%ld", west);
    fprintf(file, "|");
    fprintf(file, "%ld", up);
    fprintf(file, "|");
    fprintf(file, "%ld", down);
    fprintf(file, "|");
    fprintf(file, "%d", iluminated);
    fprintf(file, "|");
    fprintf(file, "%s", description);
    fprintf(file, "|");
    fprintf(file, "%s", description2);
    fprintf(file, "|");
    fprintf(file, "%s", icon);
    fprintf(file, "|");
    fprintf(file, "%s", icon2);
    fprintf(file, "|");
    fprintf(file, "%s", icon3);
    fprintf(file, "|");
    fprintf(file, "\n");
  }
  fprintf(file, "\n");
  fclose(file);

  return OK;
}

STATUS game_save_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  Id id = NO_ID, location = NO_ID, open = NO_ID, dependency = NO_ID, incompatible = NO_ID;
  Object *object = NULL;
  BOOL movable, hidden, illuminate, turnedon;
  int i;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "a");
  if (file == NULL)
  {
    return ERROR;
  }

  for (i = 0; i<20; i++)
  {
    object = game_get_object_i(game, i);
    if (object != NULL)
    {
      id = object_get_id(object);
      strcpy(name, object_get_name(object));
      location = game_get_object_location(game, id);
      strcpy(description, object_get_description(object));
      movable = object_get_propMovable(object);
      hidden = object_get_propHidden(object);
      illuminate = object_get_propIlluminate(object);
      turnedon = object_get_propTurnedOn(object);
      open = object_get_propOpen(object);
      dependency = object_get_propDependency(object);
      incompatible = object_get_propIncompatible(object);
    }
    fprintf(file, "#o:");
    fprintf(file, "%ld", id);
    fprintf(file, "|");
    fprintf(file, "%s", name);
    fprintf(file, "|");
    fprintf(file, "%ld", location);
    fprintf(file, "|");
    fprintf(file, "%s", description);
    fprintf(file, "|");
    fprintf(file, "%d", movable);
    fprintf(file, "|");
    fprintf(file, "%d", hidden);
    fprintf(file, "|");
    fprintf(file, "%d", illuminate);
    fprintf(file, "|");
    fprintf(file, "%d", turnedon);
    fprintf(file, "|");
    fprintf(file, "%ld", open);
    fprintf(file, "|");
    fprintf(file, "%ld", dependency);
    fprintf(file, "|");
    fprintf(file, "%ld", incompatible);
    fprintf(file, "|");
    fprintf(file, "\n");
  }
fprintf(file, "\n");
fclose(file);

return OK;
}

STATUS game_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID, open = NO_ID, dependency = NO_ID, incompatible = NO_ID;
  Object *object = NULL;
  STATUS status = OK;
  BOOL movable, hidden, illuminate, turnedon;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      if(location == NO_ID){
        player_add_object(game_get_player_i(game, 0), id);
      }
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      hidden = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atol(toks);
      toks = strtok(NULL, "|");
      turnedon = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      incompatible = atol(toks);
      toks = strtok(NULL, "|");

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|\n", id, name, location, description);
#endif
      object = object_create(id);
      if (object != NULL)
      {
        object_set_name(object, name);
        game_add_object(game, object);
        game_set_object_location(game, location, id);
        object_set_description(object, description);
        object_set_propMovable(object, movable);
        object_set_propHidden(object, hidden);
        object_set_propIlluminate(object, illuminate);
        object_set_propTurnedOn(object, turnedon);
        object_set_propOpen(object, open);
        object_set_propDependency(object, dependency);
        object_set_propIncompatible(object, incompatible);
      }
    }
  }

  if (ferror(file))
    status = ERROR;

  fclose(file);

  return status;
}

STATUS game_load_players(Game *game, char *filename)
{
  FILE *file = NULL;
  char name[WORD_SIZE] = "";
  Id id = NO_ID;
  STATUS status = OK;
  Player *player;
  Id location;
  char *toks, line[WORD_SIZE] = "";

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
#endif
      player = player_create(id);
      if (player != NULL)
      {
        player_set_name(player, name);
        game_add_player(game, player);
        game_set_player_location(game, location);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

STATUS game_save_players(Game *game, char *filename)
{
  FILE *file = NULL;
  char name[WORD_SIZE] = "";
  Id id = NO_ID, location = NO_ID;
  Player *player = NULL;
  int i;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "a");
  if (file == NULL)
  {
    return ERROR;
  }

  for (i = 0; game_get_player_i(game, i) != NULL; i++)
  {
    player = game_get_player_i(game, i);
    if (player != NULL)
    {
      id = player_get_id(player);
      strcpy(name, player_get_name(player));
      location = game_get_player_location(game);
    }
    fprintf(file, "#p:");
    fprintf(file, "%ld", id);
    fprintf(file, "|");
    fprintf(file,"%s",name);
    fprintf(file, "|");
    fprintf(file, "%ld", location);
    fprintf(file, "\n");
  }
fprintf(file, "\n");
fclose(file);

return OK;
}



STATUS game_save_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char name[WORD_SIZE] = "";
  Id id = NO_ID, id1 = NO_ID, id2 = NO_ID;
  CONNECTION state;
  Link *link = NULL;
  int i;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "a");
  if (file == NULL)
  {
    return ERROR;
  }

  for (i = 0; game_get_link_i(game, i) != NULL; i++)
  {
    link = game_get_link_i(game, i);
    if (link != NULL)
    {
      id = link_get_idLink(link);
      strcpy(name, link_get_name(link));
      id1 = link_get_id1(link);
      id2 = link_get_id2(link);
      state = link_get_status(link);
    }
    fprintf(file, "#l:");
    fprintf(file, "%ld", id);
    fprintf(file, "|");
    fprintf(file, "%s", name);
    fprintf(file, "|");
    fprintf(file, "%li", id1);
    fprintf(file, "|");
    fprintf(file, "%li", id2);
    fprintf(file, "|");
    fprintf(file, "%i", state);
    fprintf(file, "\n");
  }
  fprintf(file, "\n");
  fclose(file);

  return OK;
}

STATUS game_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL, name[WORD_SIZE] = "";
  Id id1 = NO_ID, id2 = NO_ID, idLink = NO_ID;
  Link *link = NULL;
  STATUS status = OK;
  CONNECTION state = OPEN;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      idLink = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id1 = atol(toks);
      toks = strtok(NULL, "|");
      id2 = atol(toks);
      toks = strtok(NULL, "|");
      state = atol(toks);
#ifdef DEBUG
      printf("Leido: %s|%ld|%ld|%d\n", name, id1, id2, state);
#endif
      link = link_create();
      if (link != NULL)
      {
        link_set_idLink(link, idLink);
        link_set_name(link, name);
        link_set_id1(link, id1);
        link_set_id2(link, id2);
        link_set_status(link, state);
        game_add_link(game, link);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }
  fclose(file);

  return status;
}

STATUS game_management_save(Game *game, char *filename)
{
  if(!game || !filename) return ERROR;

  game_save_spaces(game, filename);
  game_save_objects(game, filename);
  game_save_players(game,filename);
  game_save_links(game,filename);
  
  return OK;
}

Game *game_management_load(Game *game, char *filename)
{
  
  if (game_create_from_file(game, filename) == ERROR){
    game_destroy(game);
    return NULL;
  }

  return game;
}
