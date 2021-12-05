CFLAGS = -Wall -ansi -pedantic -g
LDLIBS = -lstack_fp -llist
IFLAGS=-I./
LDFLAGS=-L./
all: p4_e2
p4_e2: p4_e2.o node.o graph_list.o queue.o liblist.a
	gcc p4_e2.o node.o graph_list.o queue.o -o p4_e2	$(LDFLAGS) $(LDLIBS)

p4_e2.o: p4_e2.c
	gcc $(CFLAGS) $(IFLAGS) -c p4_e2.c -g

node.o: node.c node.h
	gcc $(CFLAGS) -c node.c -g

graph_list.o: graph_list.c graph.h liblist.a
	gcc $(CFLAGS) -c graph_list.c -g


clean:
	rm *.o 
	rm p4_e1