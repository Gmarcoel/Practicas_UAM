CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./

DIR = ~/Prog2/practicas/TASK02/recursos/
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
all: p2_e3
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'
########################################################################


p2_e3: p2_e3.o stack.o element.o
	$(CC) -o $@ $< $(LDFLAGS) stack.o element.o

p2_e3.o: p2_e3.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

stack.o: stack.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

element.o: element.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

clean:
	rm *.o