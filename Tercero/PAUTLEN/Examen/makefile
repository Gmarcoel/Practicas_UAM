CC = gcc
BISON = bison
FLEX = flex
ALFA=./alfa
ALIB = alfalib/alfalib.o

BIN = alfa
CFLAGS = -Wall
CYYFLAGS = 

FLEXFLAGS =

BISONFLAGS = -dyv

OBJ = tablaSimbolos.o tabla.o generacion.o

all: ${BIN}

alfa: y.tab.o lex.yy.o compiler.o $(OBJ)
	$(CC) -o $(ALFA) $^

lex.yy.o: lex.yy.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

y.tab.o: y.tab.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

%.o: %.c
	$(CC) ${CFLAGS} -c -o $@ $<

y.tab.c: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

y.tab.h: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

lex.yy.c: alfa.l y.tab.h
	$(FLEX) $(FLEXFLAGS) alfa.l

clean: 
	rm -rvf $(BIN) *.o lex.yy.c y.tab.h y.tab.c y.output alfa tests/*

test_condicionales: alfa tests/
	./alfa ejemplos_compilador/ejemplo_condicionales/condicionales.alfa tests/condicionales.asm
	nasm -felf32 tests/condicionales.asm
	gcc -m32 -no-pie -o tests/condicionales tests/condicionales.o $(ALIB)

test_factorial: alfa tests/
	./alfa ejemplos_compilador/ejemplo_factorial/factorial.alfa tests/factorial.asm
	nasm -felf32 tests/factorial.asm
	gcc -m32 -no-pie -o tests/factorial tests/factorial.o $(ALIB)

test_fibonacci: alfa tests/
	./alfa ejemplos_compilador/ejemplo_fibonacci/fibonacci.alfa tests/fibonacci.asm
	nasm -felf32 tests/fibonacci.asm
	gcc -m32 -no-pie -o tests/fibonacci tests/fibonacci.o $(ALIB)

test_funciones: alfa tests/
	./alfa ejemplos_compilador/ejemplo_funciones/funciones.alfa tests/funciones.asm
	nasm -felf32 tests/funciones.asm
	gcc -m32 -no-pie -o tests/funciones tests/funciones.o $(ALIB)

test_funciones_vectores: alfa tests/
	./alfa ejemplos_compilador/ejemplo_funciones_vectores/funciones_vectores.alfa tests/funciones_vectores.asm
	nasm -felf32 tests/funciones_vectores.asm
	gcc -m32 -no-pie -o tests/funciones_vectores tests/funciones_vectores.o $(ALIB)

test_adicional: alfa tests/
	./alfa ejemplos_compilador/test_adicional.alfa tests/test_adicional.asm
	nasm -felf32 tests/test_adicional.asm
	gcc -m32 -no-pie -o tests/test_adicional tests/test_adicional.o $(ALIB)

test_adicional%: alfa tests/
	./alfa ejemplos_compilador/$@.alfa tests/$@.asm
	nasm -felf32 tests/$@.asm
	gcc -m32 -no-pie -o tests/$@ tests/$@.o $(ALIB)

examen: alfa
	./alfa examen.alfa examen.asm
	nasm -felf32 examen.asm
	gcc -m32 -no-pie -o examen examen.o $(ALIB)

examen2: alfa
	./alfa examen2.alfa examen2.txt
	nasm -felf32 examen2.asm
	gcc -m32 -no-pie -o examen2 examen2.o $(ALIB)

tests/:
	mkdir -p tests