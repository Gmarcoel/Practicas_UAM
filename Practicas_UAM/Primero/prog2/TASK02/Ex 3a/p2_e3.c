/*
* File: p2_e3.c
* Author: Guillermo Martín-Coello & Gonzalo Mejías 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "element.h"
#define WORD_SIZE 30



Status reverseWords(char *strout, char *strin);

int main()
{
    char in[WORD_SIZE], out[WORD_SIZE];
    int i;
    for (i = 0; i < WORD_SIZE; i++)
        in[i] = ' ';
    gets(in);
      in[strlen(in)+1]='\0';   
    reverseWords(out, in);
    printf("%s",out);
}

Status reverseWords(char *strout, char *strin)
{
    /*Initialitation*/
    int i, c = 0,j=0;
    Stack *s = NULL;
    Element *e = NULL,*aux;
    if(!(s = stack_init() ))
        return ERROR;
    if(!(aux = element_init() ))
        return ERROR;

    /*Error control*/
    if (strin == NULL)
        return ERROR;


    while (strin[c]!='\0')
    {
    /*Stack push*/
        for (i = c; strin[i] != ' ' && strin[i]!='\0'; i++, c++)
        {
            element_setInfo(aux,&strin[i]);
            if((stack_push(s, aux) )== ERROR)
            return ERROR;
        }
        c++;

    /*Stack pop*/
        while (stack_isEmpty(s) == FALSE)
        {
            e = stack_pop(s);
            strout[j] = *((char*)element_getInfo(e));
            j++;
            element_free(e);
        }

        strout[j] = ' ';
        j++;

    }
    strout[j] = '\0';
    stack_free(s);
    element_free(aux);
    return OK;
}
