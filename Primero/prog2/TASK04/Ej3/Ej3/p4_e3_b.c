#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "types.h"
#include "stack_fp.h"
#include "tree.h"
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#define MAX_ID 1000
#define SIZE 2
typedef int (*f_cmp_type)(const void *, const void *);

/**ut, f_cmp_type fun);
* @brief This functión insert n random integers between 0 and MAX_ID into
* an ordered list.
*
* This functions modifies the list input parameter.
*
* @param n, Length of the list
* @param ppl, Address of object list
* @return This function returns OK or ERROR.
**/
Status listRandomAndOrdered(const int n, List *pl[]);

int main(int argc, char **argv)
{
    List *l[SIZE];
    BSTree *tree1, *tree2;
    int *ele = NULL;
    if (!argv[1] || argv[2])
    {
        printf("Wrong arguments. Please write only an integer as number of elements of the lists");
        return -1;
    }
    /*List init*/
    l[0] = list_new(int_free, int_copy, int_print, int_cmp);
    l[1] = list_new(int_free, int_copy, int_print, int_cmp);
    if (!l[0] || !l[1] )
    {
        list_free(l[0]);
        list_free(l[1]);;
        return -1;
    }
    /*Add randorm order*/
    if (listRandomAndOrdered(atoi(argv[1]), l) == ERROR)
    {
        list_free(l[0]);
        list_free(l[1]);
        return -1;
    }
    /*Tree*/
    tree1 = tree_init(int_free, int_copy, int_print, int_cmp);
    tree2 = tree_init(int_free, int_copy, int_print, int_cmp);

    /*print*/
    list_print(stdout,l[0]);
    printf("\n");
    list_print(stdout,l[1]);
    printf("\n");
    /*
    printf("List 01:\n");
    while (list_isEmpty(l[0]) == FALSE)
    {
        ele = list_popFront(l[0]);
        int_print(stdout, ele);
        printf(" ");
        int_free(ele);
    }
    printf(" size: %i", atoi(argv[1]));
    printf("\nList 02:\n");
    while (list_isEmpty(l[1]) == FALSE)
    {
        ele = list_popFront(l[1]);
        int_print(stdout, ele);
        printf(" ");
        int_free(ele);
    }
    printf(" size: %i\n", atoi(argv[1]));
    */

    /*Tree implementation*/
    while(list_isEmpty(l[0])==FALSE)
    {
        ele = list_popFront(l[0]);
        int_print(stdout,ele);
        tree_insert(tree1, ele);
        int_free(ele);
        ele = list_popFront(l[1]);
        tree_insert(tree2,ele);
        int_free(ele);
    }
    printf("\nTree 1 depth: %i\n", tree_depth(tree1));
    
    printf("TREE 1 PREORDER:\n");
    tree_preOrder(stdout,tree1);
    printf("TREE 1 INORDER:\n");
    tree_inOrder(stdout,tree1);
    printf("TREE 1 POSTORDER:\n");
    tree_postOrder(stdout,tree1);    
    printf("--------------------\n");
    printf("Tree 2 depth: %i\n", tree_depth(tree2));

    printf("TREE 2 PREORDER:\n");
    tree_preOrder(stdout,tree2);
    printf("TREE 2 INORDER:\n");
    tree_inOrder(stdout,tree2);
    printf("TREE 2 POSTORDER:\n");
    tree_postOrder(stdout,tree2); 
    

    list_free(l[0]);
    list_free(l[1]);
    tree_destroy(tree1);
    tree_destroy(tree2);
    return 0;
}

Status listRandomAndOrdered(const int n, List *pl[])
{
    int i, *x;
    Status st = OK;
    x=(int*)calloc(n,sizeof(int));
    
    if (!pl)
        return ERROR;

    for (i = 0; i < n && st == OK; i++)
    {
        x[i] = rand() % MAX_ID;
        st = list_pushFront(pl[0], &x[i]);
        list_pushOrder(pl[1],&x[i],1);
    }
    if (st == ERROR)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }
    free (x);
    
    return OK;
}