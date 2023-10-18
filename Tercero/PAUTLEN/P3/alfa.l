%{
    #include <stdio.h>
    #include "y.tab.h"
    int line = 1, col = 1;
    int morph_error = 0;
    extern FILE *out;
%}

%option noyywrap

alpha [[:alpha:]]
alphanum [[:alpha:][:digit:]]

%%

 /* Palabras reservadas */

"main"                  {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAIN;}     
"int"                   {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_INT;}
"boolean"               {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_BOOLEAN;}
"array"                 {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ARRAY;}
"function"              {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_FUNCTION;}            
"if"                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IF;}
"else"                  {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ELSE;}               
"while"                 {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_WHILE;}       
"scanf"                 {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_SCANF;}       
"printf"                {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PRINTF;}      
"return"                {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_RETURN;}   

 /* Symbols */

";"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA;}
","                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_COMA;}
"("                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PARENTESISIZQUIERDO;}
")"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_PARENTESISDERECHO;}
"["                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CORCHETEIZQUIERDO;}
"]"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CORCHETEDERECHO;}
"{"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_LLAVEIZQUIERDA;}
"}"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_LLAVEDERECHA;}
"="                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ASIGNACION;}
"+"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAS;}
"-"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENOS;}
"/"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_DIVISION;}
"*"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_ASTERISCO;}
"&&"                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_AND;}
"||"                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_OR;}
"!"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_NOT;}
"=="                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!="                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"<="                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
">="                    {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
"<"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MENOR;}
">"                     {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_MAYOR;}

 /* Constants */ 

[[:digit:]]+            {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}
"true"                  {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_TRUE;}
"false"                 {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_FALSE;}

 /* Ignore whitespace and comments */

"\t"                    {col+=yyleng;}
"\n"                    {line++;col=1;}
" "                     {col+=1;}
"//".*                  {col+=yyleng;}

 /* Error if it finds a string longer than 100 characters */

{alpha}{alphanum}{100,}            {morph_error = 1;
                                    fprintf(stderr, "****Error in [lin %i, col %i]: identifier too long (%s)\n", line, col, yytext);
                                    return TOK_ERROR;}

 /* Identifier */

{alpha}{alphanum}*                 {col+=yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IDENTIFICADOR;}

 /* Unidentified character */

.                                  {morph_error = 1;
                                    fprintf(stderr, "****Error en [lin %i, col %i]: simbolo no permitido (%s)\n", line, col, yytext);
                                    return TOK_ERROR;}

%%
