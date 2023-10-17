CFLAGS= -Wall -ansi -pedantic -Isrc -Iinclude -Iobj -Idoc
D = ./doc
all: doxygen game

game: object.o player.o command.o game.o game_loop.o graphic_engine.o screen.o space.o game_management.o set.o die.o inventory.o link.o
	gcc -g obj/command.o obj/game.o obj/game_loop.o obj/graphic_engine.o obj/screen.o obj/space.o obj/game_management.o obj/player.o obj/object.o obj/set.o obj/die.o obj/inventory.o obj/link.o -o  game -g

object.o: src/object.c include/object.h
	gcc $(CFLAGS) -c src/object.c -g
	mv object.o ./obj

player.o: src/player.c include/player.h
	gcc $(CFLAGS) -c src/player.c -g
	mv player.o ./obj

command.o: src/command.c include/command.h
	gcc $(CFLAGS) -c src/command.c
	mv command.o ./obj

game.o: src/game.c include/game.h
	gcc $(CFLAGS) -c src/game.c -g
	mv game.o ./obj

die.o: src/die.c include/die.h
	gcc $(CFLAGS) -c src/die.c -g
	mv die.o ./obj

game_loop.o: src/game_loop.c
	gcc $(CFLAGS) -c src/game_loop.c -g
	mv game_loop.o ./obj

graphic_engine.o: src/graphic_engine.c include/graphic_engine.h
	gcc  $(CFLAGS) -c src/graphic_engine.c -g
	mv graphic_engine.o ./obj

screen.o: src/screen.c include/screen.h
	gcc  $(CFLAGS) -c src/screen.c -g
	mv screen.o ./obj

space.o: src/space.c include/space.h
	gcc $(CFLAGS) -c src/space.c -g
	mv space.o ./obj

game_management.o: src/game_management.c include/game_management.h
	gcc $(CFLAGS) -c src/game_management.c -g
	mv game_management.o ./obj

set.o: src/set.c include/set.h
	gcc $(CFLAGS) -c src/set.c -g
	mv set.o ./obj

inventory.o: src/inventory.c include/inventory.h
	gcc $(CFLAGS) -c src/inventory.c -g
	mv inventory.o ./obj

link.o: src/link.c include/link.h
	gcc $(CFLAGS) -c src/link.c -g
	mv link.o ./obj

set_test:  set.o set_test.o
	gcc obj/set.o obj/set_test.o -o set_test -g

set_test.o: src/set_test.c
	gcc $(CFLAGS) -c src/set_test.c -g
	mv set_test.o ./obj

die_test:  die.o die_test.o
	gcc obj/die.o obj/die_test.o $(CFLAGS) -o die_test -g

die_test.o: src/die_test.c
	gcc $(CFLAGS) -c src/die_test.c -g
	mv die_test.o ./obj

object_test: object.o object_test.o 
	gcc $(CFLAGS)-c obj/object.o obj/object_test.o -o object_test -g

object_test.o: src/object_test.c
	gcc $(CFLAGS) -c src/object_test.c -g
	mv object_test.o ./obj

space_test: space.o set.o space_test.o
	gcc obj/space.o obj/set.o obj/space_test.o $(CFLAGS) -o space_test -g

space_test.o: src/space_test.c
	gcc $(CFLAGS) -c src/space_test.c -g
	mv space_test.o ./obj

player_test: player.o set.o player_test.o inventory.o object.o
	gcc obj/player.o obj/set.o obj/inventory.o obj/object.o obj/player_test.o $(CFLAGS) -o player_test -g

player_test.o: src/player_test.c
	gcc $(CFLAGS) -c src/player_test.c -g
	mv player_test.o ./obj

clean:
	rm obj/*.o game

doxygen:
	> doxygen $(D) -g
	> doxygen $(D)/Doxyfile





