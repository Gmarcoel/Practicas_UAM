all: Pract3.exe

Pract3.exe: Pract3.obj Pract3a.obj Pract3b.obj
	tcc -v -ml -Lc:\compila\tc\lib Pract3.obj Pract3a.obj Pract3b.obj
	
Pract3.obj: pract3.c
	tcc -c -v -ml -Ic:\compila\tc\include pract3.c

Pract3a.obj: pract3a.asm
	tasm /zi /ml pract3a.asm,, pract3a.lst
	
Pract3b.obj: pract3b.asm
	tasm /zi /ml pract3b.asm,, pract3b.lst