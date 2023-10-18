%{
    #include <stdio.h>
    #include "tokens.h"
    int line = 1, col = 1;
%}

%option noyywrap

alpha [[:alpha:]]
alphanum [[:alpha:][:digit:]]

%%

 /* Palabras reservadas */

"main"                  {col+=yyleng;return TOK_MAIN;}     
"int"                   {col+=yyleng;return TOK_INT;}
"boolean"               {col+=yyleng;return TOK_BOOLEAN;}
"array"                 {col+=yyleng;return TOK_ARRAY;}
"function"              {col+=yyleng;return TOK_FUNCTION;}            
"if"                    {col+=yyleng;return TOK_IF;}
"else"                  {col+=yyleng;return TOK_ELSE;}               
"while"                 {col+=yyleng;return TOK_WHILE;}       
"scanf"                 {col+=yyleng;return TOK_SCANF;}       
"printf"                {col+=yyleng;return TOK_PRINTF;}      
"return"                {col+=yyleng;return TOK_RETURN;}   

 /* Symbols */

";"                     {col+=yyleng;return TOK_PUNTOYCOMA;}
","                     {col+=yyleng;return TOK_COMA;}
"("                     {col+=yyleng;return TOK_PARENTESISIZQUIERDO;}
")"                     {col+=yyleng;return TOK_PARENTESISDERECHO;}
"["                     {col+=yyleng;return TOK_CORCHETEIZQUIERDO;}
"]"                     {col+=yyleng;return TOK_CORCHETEDERECHO;}
"{"                     {col+=yyleng;return TOK_LLAVEIZQUIERDA;}
"}"                     {col+=yyleng;return TOK_LLAVEDERECHA;}
"="                     {col+=yyleng;return TOK_ASIGNACION;}
"+"                     {col+=yyleng;return TOK_MAS;}
"-"                     {col+=yyleng;return TOK_MENOS;}
"/"                     {col+=yyleng;return TOK_DIVISION;}
"*"                     {col+=yyleng;return TOK_ASTERISCO;}
"&"                     {col+=yyleng;return TOK_AND;}
"|"                     {col+=yyleng;return TOK_OR;}
"^"                     {col+=yyleng;return TOK_NOT;}
"=="                    {col+=yyleng;return TOK_IGUAL;}
"!="                    {col+=yyleng;return TOK_DISTINTO;}
"<="                    {col+=yyleng;return TOK_MENORIGUAL;}
">="                    {col+=yyleng;return TOK_MAYORIGUAL;}
"<"                     {col+=yyleng;return TOK_MENOR;}
">"                     {col+=yyleng;return TOK_MAYOR;}

 /* Constants */ 

[[:digit:]]+            {col+=yyleng;return TOK_CONSTANTE_ENTERA;}
"true"                  {col+=yyleng;return TOK_TRUE;}
"false"                 {col+=yyleng;return TOK_FALSE;}

 /* Ignore whitespace and comments */

"\t"                    {col+=yyleng;}
"\n"                    {line++;col=1;}
" "                     {col+=1;}
"//".*                  {col+=yyleng;}

 /* Error if it finds a string longer than 100 characters */

{alpha}{alphanum}{100,}            {return TOK_ERROR;}

 /* Identifier */

{alpha}{alphanum}*                 {col+=yyleng;return TOK_IDENTIFICADOR;}

%%
