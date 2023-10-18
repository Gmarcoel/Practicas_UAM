CFLAGS = -Wall -pedantic -g

all: pruebaSintactico

lex.yy.c: alfa.l
	flex alfa.l

lex.yy.o: lex.yy.c
	gcc $(CFLAGS) -c $<

y.tab.c: alfa.y
	bison -d -y -v alfa.y

y.tab.o: y.tab.c
	gcc $(CFLAGS) -c $<

pruebaSintactico.o: pruebaSintactico.c y.tab.c
	gcc $(CFLAGS) -c $<

pruebaSintactico: pruebaSintactico.o y.tab.o lex.yy.o
	gcc $^ -o $@ 

clean:
	rm -rf lex.yy.c *.o pruebaMorpho y.tab.* y.output pruebaSintactico
