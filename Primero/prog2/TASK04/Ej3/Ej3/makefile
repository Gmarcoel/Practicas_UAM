CFLAGS = -Wall -ansi -pedantic -g
LDLIBS = -llist -lstack_fp
IFLAGS=-I./
LDFLAGS=-L./
all: p4_e3_b p4_e3_a
p4_e3_a: p4_e3_a.o node.o graph.o tree.o liblist.a
	gcc p4_e3_a.o node.o graph.o tree.o -o p4_e3_a	$(LDFLAGS) $(LDLIBS)

p4_e3_b: p4_e3_b.o node.o graph.o tree.o liblist.a
	gcc p4_e3_b.o node.o graph.o tree.o -o p4_e3_b	$(LDFLAGS) $(LDLIBS)

p4_e3_a.o: p4_e3_a.c
	gcc $(CFLAGS) $(IFLAGS) -c p4_e3_a.c -g

p4_e3_b.o: p4_e3_b.c libstack_fp.a liblist.a
	gcc $(CFLAGS) $(IFLAGS) -c p4_e3_b.c -g

node.o: node.c node.h
	gcc $(CFLAGS) -c node.c -g

graph.o: graph.c graph.h liblist.a
	gcc $(CFLAGS) -c graph.c -g

tree.o: tree.c
	gcc $(CFLAGS) -c tree.c


clean:
	rm *.o 
	rm p4_e3_a
