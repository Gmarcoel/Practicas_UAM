CFLAGS = -Wall -ansi -pedantic -g
LDLIBS = -lstack_fp
IFLAGS=-I./
LDFLAGS=-L./
all: p3_e3 p3_e3_c

p3_e3: p3_e3.o node.o graph.o queue.o
	gcc p3_e3.o node.o graph.o queue.o -o p3_e3	

p3_e3_c: p3_e3_c.o node.o graph.o queue.o libstack_fp.a
	gcc p3_e3_c.o node.o graph.o queue.o -o  p3_e3_c	$(LDFLAGS) $(LDLIBS)

p3_e3.o: p3_e3.c libstack_fp.a
	gcc $(CFLAGS) -c p3_e3.c -g

p3_e3_c.o: p3_e3_c.c libstack_fp.a
	gcc $(CFLAGS) $(IFLAGS) -c p3_e3_c.c -g

node.o: node.c node.h
	gcc $(CFLAGS) -c node.c -g

graph.o: graph.c graph.h
	gcc $(CFLAGS) -c graph.c -g

queue.o: queue.c queue.h
	gcc $(FLAGS) -c queue.c -g


clean:
	rm *.o 
	rm p3_e3
