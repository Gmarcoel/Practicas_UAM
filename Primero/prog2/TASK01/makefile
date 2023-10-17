CFLAGS = -Wall -ansi -pedantic
all: p1_e2 p1_e1 p1_e3

p1_e1: p1_e1.o node.o
	gcc p1_e1.o node.o -o p1_e1

p1_e2: p1_e2.o node.o graph.o
	gcc p1_e2.o node.o graph.o -o p1_e2

p1_e3: p1_e3.o node.o graph.o
	gcc p1_e3.o node.o graph.o -o p1_e3	

p1_e1.o: p1_e1.c
	gcc $(CFLAGS) -c p1_e1.c	

p1_e2.o: p1_e2.c
	gcc $(CFLAGS) -c p1_e2.c

p1_e3.o: p1_e3.c
	gcc $(CFLAGS) -c p1_e3.c

node.o: node.c
	gcc $(CFLAGS) -c node.c

graph.o: graph.c
	gcc $(CFLAGS) -c graph.c

clean:
	rm *.o 
	rm p1_e1 p1_e2 p1_e3
