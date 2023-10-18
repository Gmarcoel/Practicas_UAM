CFLAGS = -Wall -pedantic -g

all: tablaSimbolos

tabla.o: tabla.c
	gcc $(CFLAGS) -c $<

tablaSimbolos.o: tablaSimbolos.c
	gcc $(CFLAGS) -c $<

tablaSimbolos: tablaSimbolos.o tabla.o
	gcc $^ -o $@ 


clean:
	rm -rf tabla tablaSimbolos *.o