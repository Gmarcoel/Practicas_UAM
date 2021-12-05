CFLAGS= -Wall -ansi -pedantic

all: game 

game: object.o player.o command.o game.o game_loop.o graphic_engine.o screen.o space.o game_reader.o set.o die.o
	gcc -g command.o game.o game_loop.o graphic_engine.o screen.o space.o game_reader.o player.o object.o set.o die.o -o game -g
	rm *.o

object.o: object.c object.h
	gcc $(CFLAGS) -c object.c

player.o: player.c player.h
	gcc $(CFLAGS) -c player.c

command.o: command.c command.h
	gcc $(CFLAGS) -c command.c

game.o: game.c game.h
	gcc $(CFLAGS) -c game.c

game_loop.o: game_loop.c
	gcc $(CFLAGS) -c game_loop.c

graphic_engine.o: graphic_engine.c graphic_engine.h
	gcc  $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	gcc  $(CFLAGS) -c screen.c

space.o: space.c space.h
	gcc $(CFLAGS) -c space.c

game_reader.o: game_reader.c game_reader.h
	gcc $(CFLAGS) -c game_reader.c

set.o: set.c set.h
	gcc $(CFLAGS) -c set.c

set_test:  set.o set_test.o
	gcc set.o set_test.o -o set_test

set_test.o: set_test.c
	gcc -c set_test.c

clean:
	rm *.o

die_test:  die.o die_test.o
	gcc die.o die_test.o -o die_test

die_test.o: die_test.c
	gcc -c die_test.c


