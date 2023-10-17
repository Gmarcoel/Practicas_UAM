/*
* File: element.h
* Author: Profesores de PROG2
*/
#ifndef ELEMENT_H
#define ELEMENT_H
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct _Element Element;
Element *element_init();
void element_free(Element *e);
Element *element_setInfo(Element * e, void * v);
void *element_getInfo(Element * e);
Element *element_copy(const Element * e);
Bool element_equals(const Element * e1, const Element * e2);
int element_print(FILE * f, const Element * e);
#endif
/* ELESTACK_H */