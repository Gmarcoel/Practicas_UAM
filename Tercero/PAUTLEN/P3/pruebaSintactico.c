#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern FILE *yyin;
FILE *out = NULL;

int main(int argc, char const *argv[])
{
    // Error control
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    // Error control
    if (!yyin)
    {
        fprintf(stderr, "Error opening input file");
        return -1;
    }
    if (!out)
    {
        fprintf(stderr, "Error opening output file");
        return -1;
    }

    yyparse();
    
    fclose(yyin);
    fclose(out);

    return 0;
}
