/** 
 * @brief It defines a player
 * 
 * @file player.c
 * @author Guillermo Martin
 * @version 1.0 
 * @date 16/02/20
 * @copyright GNU Public License
 */

#include "player.h"
#define str 255
struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Inventory *backpack;
};

Player* player_create(Id id){

  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player));

  if (newPlayer == NULL) {
    return NULL;
  }
  newPlayer->id = id;

  newPlayer->name[0] = '\0';

  newPlayer->location = NO_ID;

  newPlayer->backpack = inventory_create();
  
  return newPlayer;
}

STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  inventory_destroy(player->backpack);

  free(player);
  player = NULL;

  return OK;
}

STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS player_set_location(Player* player, Id location) {
  if (!player || location==NO_ID) {
    return ERROR;
  }
  player->location = location;
  return OK;
}

STATUS player_is_object(Player* player, Id id){
  if (!player) {
    return ERROR;
  }
  return inventory_is_object(player->backpack, id);
}

STATUS player_add_object(Player* player, Id value) {
  
  if (!player) return ERROR;

  return inventory_add_object(player->backpack, value);
}

STATUS player_del_object(Player* player,Id id){

	if (player == NULL || id==NO_ID){
		return ERROR;
	}

  return inventory_del_object(player->backpack,id);
}

const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/*int player_get_object(Player* player, Id id) {
  
  int numObj, i;

  if (!player) {
    return -1;
  }

  i = inventory_get_objects(player->backpack, id);

    if (i < 0) return -1;

  return i;
}  
OBSOLETA*/

Id *player_get_objects(Player* player){

  if(!player) return NULL;

  return inventory_get_objects(player->backpack);
}

/*STATUS player_set_inventory(Player * player, Inventory * backpack)
{
  if(!player||!backpack) return ERROR;
  player->backpack = backpack;
  return OK;
}   BACKPACK YA CREADA EN PLAYER CREATE*/ 

Inventory *player_get_inventory(Player * player)
{
  if(!player) return NULL;
  return player->backpack;
}

STATUS player_print(Player* player) {
  Id idaux = NO_ID;
  int i;

  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

 idaux = player_get_location(player);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }
  for (i=0;player_get_objects(player)[i]!=NO_ID;i++)
  {
    fprintf(stdout,"Object %i: %ld\n",i,player_get_objects(player)[i]);
  }
  /*
  for(i=0; idaux!=NO_ID; i++){}
  if (player_get_object(player, idaux)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }*/

  return OK;
}
