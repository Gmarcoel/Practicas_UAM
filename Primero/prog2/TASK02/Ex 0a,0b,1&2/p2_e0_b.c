                                                                                #include "stdio.h"
#include <stdlib.h>
#include "stack_fp.h"
#include "node.h"

int main(){
    Node* n;
    Stack* ss, *sn,*eles,*elen;
    n = node_init();


    ss = stack_init (string_free, string_copy, string_print);
    sn = stack_init (node_free, node_copy, node_print);

    node_setName(n, "first");
	node_setId(n, 111);
	node_setLabel(n, WHITE);

    stack_push (sn, n);
    stack_push (ss, node_getName(n));

    node_setName(n, "second");
	node_setId(n, 222);
	node_setLabel(n, WHITE);

    stack_push (sn, n);
    stack_push (ss, node_getName(n));

    stack_print(stdout,ss);
    stack_print(stdout,sn);

    while ( stack_isEmpty(sn) == FALSE ) {
        elen = stack_pop (sn);
        fprintf(stdout, "Extracted element:");
        node_print(stdout,elen);  
        fprintf(stdout,"\n");
    }

    while ( stack_isEmpty(ss) == FALSE ) {
        eles = stack_pop (ss);
        fprintf(stdout, "Extracted element:");
        string_print (stdout, eles);   
        fprintf(stdout,"\n");
    }

    stack_free(sn);
    stack_free(ss);
}