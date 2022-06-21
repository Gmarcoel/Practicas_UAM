all: Pract3b.exe

Pract3b.exe: Prac3bc.obj Pract3b.obj
	tcc -v -ml -Lc:\compila\tc\lib Prac3bc.obj Pract3b.obj
	
Prac3bc.obj: Prac3bc.c
	tcc -c -v -ml -Ic:\compila\tc\include Prac3bc.c


Pract3b.obj: pract3b.asm
	tasm /zi /ml pract3b.asm,, pract3b.lst