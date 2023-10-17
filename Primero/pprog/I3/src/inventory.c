/***
 * @brief It defines an inventory
 * @file inventory.c
 * @author Gabriela TrabajO
 * @version 1.0 
 * @date 21/03/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define MAX_OBJ 5

struct _Inventory {
    Set *objects;
    int MAXOBJ;
};

Inventory* inventory_create(){
    
    Inventory *newInventory = NULL;

    newInventory=(Inventory *) malloc(sizeof (Inventory));

    if (newInventory == NULL){
        return NULL;
    }

    newInventory->objects = set_create();
    newInventory->MAXOBJ = MAX_OBJ;

    return newInventory;
}

STATUS inventory_destroy(Inventory *in){

    if (in == NULL) return ERROR;

    set_destroy(in->objects);
    free(in);
    in = NULL;

    return OK;
}

STATUS inventory_add_object(Inventory *in, Id id){

    if (in == NULL || id == NO_ID) return ERROR;

    if (inventory_get_NumObjects(in)<inventory_get_maxobj(in)){

        if (set_addId(in->objects, id) == ERROR) return ERROR;

        return OK;
    }

    return ERROR;
}

STATUS inventory_is_object(Inventory *in, Id id){

    if (in == NULL || id == NO_ID) return ERROR;

    return set_is_id(in->objects, id);
}

STATUS inventory_print(Inventory *in){

    int num;

    if (in == NULL) return ERROR;

    num = inventory_get_maxobj(in);

    fprintf(stdout,"Max num objects: %d\n", num);

    set_print(stdout, in->objects);

    return OK;
}

/*delete object*/
STATUS inventory_del_object(Inventory *in, Id id){

    if (in == NULL) return ERROR;

    return set_delId(in->objects, id);
}

/*max obj*/
int inventory_get_maxobj(Inventory *in){

    if (in == NULL) return -1;

    return in->MAXOBJ;

}

STATUS inventory_set_maxobj(Inventory *in, int i){

    if (in == NULL) return ERROR;

    in->MAXOBJ=i;

    return OK;

}
/*get num of obj*/
int inventory_get_NumObjects(Inventory *in){

    if (in == NULL) return -1;

    return set_get_num(in->objects);
}

Id *inventory_get_objects(Inventory *in){

    if(in == NULL) return NULL;

    return set_get_id(in->objects);
}

Set *inventory_get_object_set(Inventory *in){

    if (in == NULL) return NULL;

    return in->objects;
}