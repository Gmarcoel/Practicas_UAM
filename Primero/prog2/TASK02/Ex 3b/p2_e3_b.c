#include "stack.h" 
#include "element.h"
int main (int argc, char **argv){
    Stack *st = NULL;
    char c[] = {'a', 'b', 'c'};
    int i = 0, len;
    Element *ele = NULL;
    Element * e;
    
// init a stack and a element
    st = stack_init ();
    e = element_init ();
    if (!st) return EXIT_FAILURE;
    len = sizeof(c)/sizeof(char);

// insert the values of the array c in the stack
    for (i = 0; i < len; i++)
    {
        element_setInfo(e,c+i);
        stack_push (st, e);
    }
// CdE, memory allocation
// Print the stack
    stack_print (stdout, st);
    fprintf (stdout, "Stack size: %d\n", stack_size (st));

// extract the last element inserted in the stack
    
    while ( stack_isEmpty(st) == FALSE ) {
        ele = stack_pop (st);
        fprintf(stdout, "Extracted element:");
        element_print (stdout, ele); 
        element_free(ele)  ;
    }

// Print the stack
    fprintf (stdout, "¥nStack size: %d\n", stack_size (st));
    stack_print (stdout, st);

// free resources
    stack_free (st);
    element_free(e);

return (EXIT_SUCCESS);
}
