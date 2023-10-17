/*
* File: element.c
* Author: Guillermo Martín-Coello & Gonzalo Mejías 
*/
#include "element.h"

struct _Element {
char *a;
};

Element *element_init()
{
    Element * e = NULL;
    if(!(e=(Element*)malloc(sizeof(Element))))
        return NULL;
    if(!(e->a=(char*)malloc(sizeof(char))))
        return NULL;
    *(e->a) = '\0';
    return e;
}

void element_free(Element *e)
{
    if(!e)
        return;
    free(e->a);
    free(e);
    return;
}

Element *element_setInfo(Element * e, void * v)
{
    char * aux = NULL;
    if(!e||!v)
        return NULL;

    aux = (char*)v;
    *(e->a) = *aux;
    return e;
}

void *element_getInfo(Element * e)
{
    void * v = NULL;
    if(!e)
        return NULL;
    v = e->a;
    return v;
}

Element *element_copy(const Element * e)
{
    Element * aux = NULL;
    if(!e)
        return NULL;
    aux = element_init();
    *(aux->a) = *(e->a);
    return aux;
}

Bool element_equals(const Element * e1, const Element * e2)
{
    if(!e1||!e2||*(e1->a)!=*(e2->a))
        return FALSE;
    return TRUE;
}

int element_print(FILE * f, const Element * e)
{
    if(!f||!e)
        return -1;
    return fprintf(f,"%c",*(e->a));
}