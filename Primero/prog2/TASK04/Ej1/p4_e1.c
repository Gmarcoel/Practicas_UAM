#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "types.h"
#include "stack_fp.h"
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#define MAX_ID 1000
typedef int (*f_cmp_type)(const void *, const void *);

/**
* @brief This function concatenate two increased ordered lists
*
* This functions does not modified the ordered input lists l1 and l2.
*
* @parameter l1, Pointer to one list
* @parameter l2, Pointer to the second list
* @parameter lout, Pointer to the output concatenated list
* @parameter fun, Function used to compare the list elements
*
3* @return This function returns OK or ERROR.
**/
Status listMergeOrdered(List *li, List *l2, List *lout, f_cmp_type fun);
/**
* @brief This functión insert n random integers between 0 and MAX_ID into
* an ordered list.
*
* This functions modifies the list input parameter.
*
* @param n, Length of the list
* @param ppl, Address of object list
* @return This function returns OK or ERROR.
**/
Status listOfRandomOrdered(int n, List *pl);

int main(int argc, char **argv)
{
    List *l1 = NULL, *l2 = NULL, *lout = NULL;
    int *ele = NULL;
    if (!argv[1] || argv[2])
    {
        printf("Wrong arguments. Please write only an integer as number of elements of the lists");
        return -1;
    }
    /*List init*/
    l1 = list_new(int_free, int_copy, int_print, int_cmp);
    l2 = list_new(int_free, int_copy, int_print, int_cmp);
    lout = list_new(int_free, int_copy, int_print, int_cmp);
    if (!l1 || !l2 || !lout)
    {
        list_free(l1);
        list_free(l2);
        list_free(lout);
        return -1;
    }
    /*Add randorm order*/
    if (listOfRandomOrdered(atoi(argv[1]), l1) == ERROR)
    {
        list_free(l1);
        list_free(l2);
        list_free(lout);
        return -1;
    }
    if (listOfRandomOrdered(atoi(argv[1]), l2) == ERROR)
    {
        list_free(l1);
        list_free(l2);
        list_free(lout);
        return -1;
    }
    /*Order*/
    if (listMergeOrdered(l1, l2, lout, int_cmp) == ERROR)
    {
        list_free(l1);
        list_free(l2);
        list_free(lout);
        return -1;
    }

    /*print*/
    printf("List 01:\n");
    while (list_isEmpty(l1) == FALSE)
    {
        ele = list_popFront(l1);
        int_print(stdout, ele);
        printf(" ");
        int_free(ele);
    }
    printf(" size: %i",atoi(argv[1]));
    printf("\nList 02:\n");
    while (list_isEmpty(l2) == FALSE)
    {
        ele = list_popFront(l2);
        int_print(stdout, ele);
        printf(" ");
        int_free(ele);
    }
    printf(" size: %i",atoi(argv[1]));
    printf("\nMerged list:\n");
    while (list_isEmpty(lout) == FALSE)
    {
        ele = list_popFront(lout);
        int_print(stdout, ele);
        printf(" ");
        int_free(ele);
    }
    printf(" size: %i",atoi(argv[1])*2);
    /*
    printf("List 01:\n");
    list_print(stdout,l1);

    list_print(stdout,l2);

    list_print(stdout,lout);
    printf("\n");
    */
    list_free(l1);
    list_free(l2);
    list_free(lout);
    return 0;
}

Status listMergeOrdered(List *l1, List *l2, List *lout, f_cmp_type fun)
{
    Stack *s1 = NULL, *s2 = NULL, *saux;
    int *ele;
    List *laux;

    if (!l1 || !l2 || !lout || !fun)
        return ERROR;

    if (!(s1 = stack_init(int_free, int_copy, int_print)))
        return ERROR;
    if (!(s2 = stack_init(int_free, int_copy, int_print)))
        return ERROR;

    while (list_isEmpty(l1) == FALSE)
    {
        ele = list_popFront(l1);
        stack_push(s1, ele);
        int_free(ele);
    }
    while (list_isEmpty(l2) == FALSE)
    {
        ele = list_popFront(l2);
        stack_push(s2, ele);
        int_free(ele);
    }
    while (stack_isEmpty(s1) == FALSE && stack_isEmpty(s2) == FALSE)
    {
        if (*(int *)stack_top(s1) > *(int *)stack_top(s2))
        {
            ele = stack_pop(s1);
            list_pushFront(l1, ele);
        }
        else
        {
            ele = stack_pop(s2);
            list_pushFront(l2, ele);
        }
        list_pushFront(lout, ele);
        int_free(ele);
    }
    if (stack_isEmpty(s1) == TRUE)
    {
        saux = s2;
        laux = l2;
    }
    else
    {
        saux = s1;
        laux = l1;
    }
    while (stack_isEmpty(saux) == FALSE)
    {
        ele = stack_pop(saux);
        list_pushFront(laux, ele);
        list_pushFront(lout, ele);
        int_free(ele);
    }
    stack_free(s1);
    stack_free(s2);
    return OK;
}

Status listOfRandomOrdered(int n, List *pl)
{
    int i, x;
    Status st = OK;
    if (!pl)
        return ERROR;
    for (i = 0; i < n && st == OK; i++)
    {
        x = rand() % MAX_ID;
        st = list_pushOrder(pl, &x, 1);
    }
    if (st == ERROR)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }
    return OK;
}