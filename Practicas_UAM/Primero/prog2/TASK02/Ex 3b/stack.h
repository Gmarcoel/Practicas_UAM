/*
* File: stack.h
stack.h
* Author: Profesores de PROG2
*/
#ifndef STACK_H
#define STACK_H
#include "element.h"
#include <stdio.h>
typedef struct _Stack Stack;

Stack *stack_init();
void stack_free(Stack * s);
Status stack_push(Stack * s, const Element * e);
Element *stack_pop(Stack * s);
Element *stack_top(const Stack * s);
Bool stack_isEmpty(const Stack * s);
Bool stack_isFull(const Stack * s);
int stack_print(FILE * f, const Stack * s);
int stack_size(Stack * s);
#endif
/* STACK_H */