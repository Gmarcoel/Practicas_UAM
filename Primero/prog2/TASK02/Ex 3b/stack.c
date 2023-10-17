/*
* File: stack.c
* Author: Guillermo Martín-Coello & Gonzalo Mejías 
*/
#include "stack.h"

#define MAXSTACK 1024
struct _Stack
{
    int top;
    Element *item[MAXSTACK];
};

Stack *stack_init()
{
    Stack* s = NULL;
    int i;
    if(!(s = (Stack*)malloc(sizeof(Stack))))
        return NULL;
    for (i=0;i<MAXSTACK;i++)
    {
        s->item[i] = NULL;
    }
    s->top = -1;
    return s;
}

void stack_free(Stack * s)
{
    int i=0;
    if(!s)
        return;
    for (i=0;i<MAXSTACK;i++)
    {
        if (s->item[i])
            element_free(s->item[i]);
    }
    free(s);
}

Status stack_push(Stack * s, const Element * e){
    Element * a = NULL;
    if(!s||!e||stack_isFull(s)==TRUE)
        return ERROR;
    if (!(a = element_copy(e)))
        return ERROR;
    (s->top)++;
    s->item[s->top] = a;
    return OK;
}

Element *stack_pop(Stack * s)
{
    Element  * a = NULL;
    if(!s||stack_isEmpty(s)==TRUE)
        return NULL;
    a = s->item[s->top];
    s->item[s->top]=NULL;
    (s->top)--;
    return a;
}

Element *stack_top(const Stack * s)
{
    Element  * a = NULL;
    if(!s||stack_isEmpty(s)==TRUE)
        return NULL;
    a = s->item[s->top];
    return a;
}

Bool stack_isEmpty(const Stack * s)
{
    if(!s||s->top!=-1)
        return FALSE;
    return TRUE;
}

Bool stack_isFull(const Stack * s)
{
    if(!s||s->top!=(MAXSTACK-1))
        return FALSE;
    return TRUE;
}

int stack_print(FILE * f, const Stack * s){
    int i,c=0;
    if(!s||!f)
        return -1;
    for (i=0;i<MAXSTACK;i++)
    {
        if(s->item[i])
            c = c + element_print(f,s->item[i]);
    }
    return c;
}

int stack_size(Stack * s)
{
    if(!s)
        return -1;
    return s->top+1;
}