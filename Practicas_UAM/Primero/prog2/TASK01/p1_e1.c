#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "node.h"

int main (){


	Node * a, * b;
	a = node_init();
	b = node_init();

    node_setName(a, "first");
	node_setId(a, 111);
	node_setLabel(a, WHITE);

	node_setName(b, "second");
	node_setId(b, 222);
	node_setLabel(b, WHITE);

    node_print(stdout, a);
    node_print(stdout, b);
    printf("\n");

    if(node_cmp(a, b) == -1){
        printf("The nodes are DIFFERENT!\n");
    } else if (node_cmp(a, b) == 1){
        printf("The nodes are EQUAL!\n");
    }

    printf("Id of first node: %ld\n", node_getId(a));
    printf("Name of second node: %s\n", node_getName(b));

    node_free(b);
    b = node_copy(a);

    node_print(stdout, a);
    node_print(stdout, b);
    printf("\n");


    if(node_cmp(a, b) == -1){
        printf("The nodes are DIFFERENT!\n");
    } else if (node_cmp(a, b) == 1){
        printf("The nodes are EQUAL!\n");
    }

    node_free(a);
    node_free(b);

    return 0;
}





























