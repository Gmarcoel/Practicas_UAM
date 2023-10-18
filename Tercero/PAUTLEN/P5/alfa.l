%{
    #include <stdio.h>
    #include "alfa.h"
    #include "y.tab.h"

    int line = 1, col = 1;
    int morph_error = 0;
    extern FILE *out;
    
    void printToken(char* token) {
    	col += yyleng;
    	fprintf(out, ";D:\t%s\n", token);
    }
%}

%option noyywrap

alpha [[:alpha:]]
alphanum [[:alpha:][:digit:]]

%%

 /* Palabras reservadas */

"main"                  {printToken(yytext); return TOK_MAIN;}     
"int"                   {printToken(yytext); return TOK_INT;}
"boolean"               {printToken(yytext); return TOK_BOOLEAN;}
"array"                 {printToken(yytext); return TOK_ARRAY;}
"function"              {printToken(yytext); return TOK_FUNCTION;}
"if"                    {printToken(yytext); return TOK_IF;}
"else"                  {printToken(yytext); return TOK_ELSE;}               
"while"                 {printToken(yytext); return TOK_WHILE;}       
"scanf"                 {printToken(yytext); return TOK_SCANF;}       
"printf"                {printToken(yytext); return TOK_PRINTF;}      
"return"                {printToken(yytext); return TOK_RETURN;}   

 /* Symbols */

";"                     {printToken(yytext); return TOK_PUNTOYCOMA;}
","                     {printToken(yytext); return TOK_COMA;}
"("                     {printToken(yytext); return TOK_PARENTESISIZQUIERDO;}
")"                     {printToken(yytext); return TOK_PARENTESISDERECHO;}
"["                     {printToken(yytext); return TOK_CORCHETEIZQUIERDO;}
"]"                     {printToken(yytext); return TOK_CORCHETEDERECHO;}
"{"                     {printToken(yytext); return TOK_LLAVEIZQUIERDA;}
"}"                     {printToken(yytext); return TOK_LLAVEDERECHA;}
"="                     {printToken(yytext); return TOK_ASIGNACION;}
"+"                     {printToken(yytext); return TOK_MAS;}
"-"                     {printToken(yytext); return TOK_MENOS;}
"/"                     {printToken(yytext); return TOK_DIVISION;}
"*"                     {printToken(yytext); return TOK_ASTERISCO;}
"&&"                    {printToken(yytext); return TOK_AND;}
"||"                    {printToken(yytext); return TOK_OR;}
"!"                     {printToken(yytext); return TOK_NOT;}
"=="                    {printToken(yytext); return TOK_IGUAL;}
"!="                    {printToken(yytext); return TOK_DISTINTO;}
"<="                    {printToken(yytext); return TOK_MENORIGUAL;}
">="                    {printToken(yytext); return TOK_MAYORIGUAL;}
"<"                     {printToken(yytext); return TOK_MENOR;}
">"                     {printToken(yytext); return TOK_MAYOR;}

 /* Constants */ 

[[:digit:]]+            {printToken(yytext); 
                        yylval.atributos.valor_entero=atoi(yytext);
                        return TOK_CONSTANTE_ENTERA;}


"true"                  {printToken(yytext); return TOK_TRUE;
                        yylval.atributos.valor_entero = 1;}
"false"                 {printToken(yytext); return TOK_FALSE;
                        yylval.atributos.valor_entero = 0;}

 /* Ignore whitespace and comments */

"\t"                    {col+=yyleng;}
"\n"                    {line++;col=1;}
" "                     {col++;}
"//".*                  {col+=yyleng;}

 /* Error if it finds a string longer than 100 characters */

{alpha}{alphanum}{100,}            {morph_error = 1;
                                    fprintf(stderr, "****Error morfológico en [lin %i, col %i]: identifier too long (%s)\n", line, col, yytext);
                                    return TOK_ERROR;}

 /* Identifier */

{alpha}{alphanum}*                 {printToken(yytext); 
                                   strcpy(yylval.atributos.lexema,yytext);
                                   return TOK_IDENTIFICADOR;}

 /* Unidentified character */

.                                  {morph_error = 1;
                                    fprintf(stderr, "****Error morfológico en [lin %i, col %i]: simbolo no permitido (%s)\n", line, col, yytext);
                                    return TOK_ERROR;}

%%