CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
DIR = ~/Prog2/practicas/TASK02/recursos/
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
all: p2_e0_a p2_e0_b p2_e1 p2_e2
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'
########################################################################

p2_e0_a: p2_e0_a.o libstack_fp.a node.o
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o

p2_e0_b: p2_e0_b.o libstack_fp.a node.o
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o

p2_e1: p2_e1.o libstack_fp.a node.o
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o

p2_e2: p2_e2.o libstack_fp.a node.o
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS) node.o

p2_e0_b.o: p2_e0_b.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e0_a.o: p2_e0_a.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1.o: p2_e1.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e2.o: p2_e2.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

node.o: node.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

clean:
	rm *.o