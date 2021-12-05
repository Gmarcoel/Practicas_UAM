CFLAGS = -Wall -ansi -pedantic -g
LDLIBS = -lstack_fp -llist
IFLAGS=-I./
LDFLAGS=-L./
all: p4_e1
p4_e1: p4_e1.o
	gcc p4_e1.o -o p4_e1 $(LDFLAGS) $(LDLIBS)

p4_e1.o: p4_e1.c libstack_fp.a liblist.a
	gcc $(CFLAGS) $(IFLAGS) -c p4_e1.c -g



clean:
	rm *.o 
	rm p4_e1