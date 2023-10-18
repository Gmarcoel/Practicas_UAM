CFLAGS = -Wall -pedantic -g

all: pruebaMorpho

lex.yy.c: alfa.l
	flex alfa.l

lex.yy.o: lex.yy.c
	gcc $(CFLAGS) -c $<

pruebaMorpho.o: pruebaMorpho.c
	gcc $(CFLAGS) -c $<

pruebaMorpho: pruebaMorpho.o lex.yy.o
	gcc $^ -o $@ 

clean:
	rm -rf alfa lex.yy.c lex.yy.o pruebaMorpho.o pruebaMorpho