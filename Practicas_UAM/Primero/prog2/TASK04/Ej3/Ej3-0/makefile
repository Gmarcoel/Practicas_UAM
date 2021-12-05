CFLAGS = -Wall -ansi -pedantic -g
LDLIBS = -llist
IFLAGS=-I./
LDFLAGS=-L./
all: p4_e3_a
p4_e3_a: p4_e3_a.o node.o graph_list.o tree.o liblist.a
	gcc p4_e3_a.o node.o graph_list.o tree.o -o p4_e3_a	$(LDFLAGS) $(LDLIBS)

p4_e3_a.o: p4_e3_a.c
	gcc $(CFLAGS) $(IFLAGS) -c p4_e3_a.c -g

node.o: node.c node.h
	gcc $(CFLAGS) -c node.c -g

graph_list.o: graph_list.c graph.h liblist.a
	gcc $(CFLAGS) -c graph_list.c -g

tree.o: tree.c
	gcc $(CFLAGS) -c tree.c


clean:
	rm *.o 
	rm p4_e1