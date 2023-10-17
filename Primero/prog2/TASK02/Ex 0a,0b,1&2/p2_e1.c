#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#define WORD_SIZE 30

Status reverseWords(char *strout, const char *strin);

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

Status reverseWords(char *strout, const char *strin)
{
    /*Initialitation*/
    int i, c = 0,j=0;
    Stack *s = NULL;
    char *a;
    if(!(s = stack_init(char_free, char_copy, char_print) ))
        return ERROR;
    
    /*Error control*/
    if (strin == NULL)
        return ERROR;


    while (strin[c]!='\0')
    {
    /*Stack push*/
        for (i = c; strin[i] != ' ' && strin[i]!='\0'; i++, c++)
        {
            if((stack_push(s, &strin[i]) )== ERROR)
            return ERROR;
        }
        c++;

    /*Stack pop*/
        while (stack_isEmpty(s) == FALSE)
        {
            a = stack_pop(s);
            strout[j] = *a;
            j++;
            char_free(a);
        }

        strout[j] = ' ';
        j++;

    }
    strout[j] = '\0';
    stack_free(s);

    return OK;
}
