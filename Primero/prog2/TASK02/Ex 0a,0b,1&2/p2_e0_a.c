#include "stack_fp.h" 
int main (int argc, char **argv){
    Stack *st = NULL;
    char c[] = {'a', 'b', 'c'};
    int i = 0, len;
    char *ele = NULL;
    
// init a stack with elements of type char
    st = stack_init (char_free, char_copy, char_print);
    if (!st) return EXIT_FAILURE;
    len = sizeof(c)/sizeof(char);

// insert the values of the array c in the stack
    for (i = 0; i < len; i++)
        stack_push (st, c+i);

// CdE, memory allocation
// Print the stack
    stack_print (stdout, st);
    fprintf (stdout, "Stack size: %ld\n", stack_size (st));

// extract the last element inserted in the stack
    
    while ( stack_isEmpty(st) == FALSE ) {
        ele = stack_pop (st);
        fprintf(stdout, "Extracted element:");
        char_print (stdout, ele);   
    }

// Print the stack
    fprintf (stdout, "¥nStack size: %ld\n", stack_size (st));
    stack_print (stdout, st);

// free resources
    char_free (ele);
    stack_free (st);

return (EXIT_SUCCESS);
}
