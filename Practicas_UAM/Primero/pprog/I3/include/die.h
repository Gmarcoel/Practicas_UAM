/**
* @brief it defines a die
*
* @file die.h
* @author Gonzalo Mejías
* @version 1.0
* @date 20/02/20
*/
#include "types.h"
#ifndef DIE_H
#define DIE_H
/*
*
*@brief elements of a die
* Defines the id and numbers of a die
*
*/
typedef struct die Die;

void die_init(void);
/***@brief It creates a new die
*
* die_create reserves memory for
* new die if it is created
*
*@date 20/02/20
*@author Gonzalo Mejías
*
* @param the identification of the die
* @return the die created
*/
Die * die_create(Id id);
/***@brief It destroys a die
*
* die_destroy deletes the die 
* and frees the memory
*
*@date 20/02/20
*@author Gonzalo Mejías
*
* @param existing die
* @return status check
*/
STATUS die_destroy(Die * die);
/***@brief It generates a random number
*
* die_roll generates a random number between 1 and 6
*
*@date 20/02/20
*@author Gonzalo Mejías
*
* @param existing die
* @return int
*/
int die_roll(Die* die);
/**
*@brief It prints the number of the die
*
* die_print shows in the screen the number generated in die_roll
*
*@date 20/02/20
*@author Gonzalo Mejías
*
* @param existing die
* @return status check
*/
STATUS die_print(Die *die);
/***
*@brief Shows last value of de die
*
*
*@date 20/02/20
*@author Guillermo Martín
*
* @param Die die
*@return int last value
**/
int die_last_value(Die* die);

#endif