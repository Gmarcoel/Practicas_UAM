#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern int line, col;

char *getTokenName(int token);

int main(int argc, char const *argv[])
{
    FILE *out = NULL;
    int tok = 0;

    // Error control
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    // Error control
    if (!yyin || !out)
    {
        fprintf(stderr, "Error opening files");
        return -1;
    }

    while ((tok = yylex()) != 0)
    {
        if (tok == TOK_ERROR)
        {
            fprintf(stderr, "****Error in [line %i, col %i]: identifier too long (%s)\n", line, col, yytext);
            break;
        }
        fprintf(out, "%s\t%i\t%s\n", getTokenName(tok), tok, yytext);
    }

    fclose(yyin);
    fclose(out);

    return 0;
}

// valgrind --leak-check=full --show-kinds=all

// flex alpha.l
// gcc -c -o lex.yy.o lex.yy.c
// gcc -Wall -ansi -pedantic -c -o pruebaMorfo.o pruebaMorfo.c
// gcc -o pruebaMorfo lex.yy.o pruebaMorfo.o
// pruebaMorfo entrada1.txt misalida1.txt

char *getTokenName(int token)
{
    switch (token)
    {
    case TOK_MAIN:
        return "TOK_MAIN";
    case TOK_INT:
        return "TOK_INT";
    case TOK_BOOLEAN:
        return "TOK_BOOLEAN";
    case TOK_ARRAY:
        return "TOK_ARRAY";
    case TOK_FUNCTION:
        return "TOK_FUNCTION";
    case TOK_IF:
        return "TOK_IF";
    case TOK_ELSE:
        return "TOK_ELSE";
    case TOK_WHILE:
        return "TOK_WHILE";
    case TOK_SCANF:
        return "TOK_SCANF";
    case TOK_PRINTF:
        return "TOK_PRINTF";
    case TOK_RETURN:
        return "TOK_RETURN";
    case TOK_PUNTOYCOMA:
        return "TOK_PUNTOYCOMA";
    case TOK_COMA:
        return "TOK_COMA";
    case TOK_PARENTESISIZQUIERDO:
        return "TOK_PARENTESISIZQUIERDO";
    case TOK_PARENTESISDERECHO:
        return "TOK_PARENTESISDERECHO";
    case TOK_CORCHETEIZQUIERDO:
        return "TOK_CORCHETEIZQUIERDO";
    case TOK_CORCHETEDERECHO:
        return "TOK_CORCHETEDERECHO";
    case TOK_LLAVEIZQUIERDA:
        return "TOK_LLAVEIZQUIERDA";
    case TOK_LLAVEDERECHA:
        return "TOK_LLAVEDERECHA";
    case TOK_ASIGNACION:
        return "TOK_ASIGNACION";
    case TOK_MAS:
        return "TOK_MAS";
    case TOK_MENOS:
        return "TOK_MENOS";
    case TOK_DIVISION:
        return "TOK_DIVISION";
    case TOK_ASTERISCO:
        return "TOK_ASTERISCO";
    case TOK_AND:
        return "TOK_AND";
    case TOK_OR:
        return "TOK_OR";
    case TOK_NOT:
        return "TOK_NOT";
    case TOK_IGUAL:
        return "TOK_IGUAL";
    case TOK_DISTINTO:
        return "TOK_DISTINTO";
    case TOK_MENORIGUAL:
        return "TOK_MENORIGUAL_MAIN";
    case TOK_MAYORIGUAL:
        return "TOK_MAYORIGUAL";
    case TOK_MENOR:
        return "TOK_MENOR";
    case TOK_MAYOR:
        return "TOK_MAYOR";
    case TOK_IDENTIFICADOR:
        return "TOK_IDENTIFICADOR";
    case TOK_CONSTANTE_ENTERA:
        return "TOK_CONSTANTE_ENTERA";
    case TOK_TRUE:
        return "TOK_TRUE";
    case TOK_FALSE:
        return "TOK_FALSE";
    case TOK_ERROR:
        return "TOK_ERROR";
    default:
        return "UNIDENTIFIED_TOKEN";
    }
    return NULL;
}
