/** 
 * @brief It loads the game space from a file
 * 
 * @file game_reader.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "space.h"
#include "game_reader.h"



STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char icon[WORD_SIZE] = "";
  char icon2[WORD_SIZE] = "";
  char icon3[WORD_SIZE] = "";  
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
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
      strcpy(icon, toks);
      toks = strtok(NULL, "|");
      strcpy(icon2, toks);
      toks = strtok(NULL, "|");
      strcpy(icon3, toks);      
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_icon(space, icon); 
  space_set_icon2(space, icon2); 
  space_set_icon3(space, icon3);  
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
	game_add_space(game, space);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}


STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object* object = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);

#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
	      object_set_name(object, name);
        game_add_object(game, object); 
        game_set_object_location(game,location,id);
      }
    }
  }
  



  if (ferror(file))
    status = ERROR;

  
  fclose(file);
  
  return status;
}