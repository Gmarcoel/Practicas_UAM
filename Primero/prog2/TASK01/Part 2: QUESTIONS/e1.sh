#!/bin/bash
gcc   -Wall -ansi -pedantic -c graph.c || gcc -Wall -ansi -pedantic -c node.c || gcc  -Wall -ansi -pedantic -c p1_e2.c ||gcc graph.o node.o p1_e2.o -o p1_e2 
#gcc -c compiles the .c files
#gcc -o links all compiled .o files into an executable program