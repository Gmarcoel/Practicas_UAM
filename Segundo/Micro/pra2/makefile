# This is a comment
all: lab2B.exe lab2C.exe lab2D.exe lab2E.exe

lab2B.exe: lab2B.obj
	tlink /v lab2B

lab2B.obj: lab2B.asm
	tasm /zi lab2B.asm ,, lab2B.lst
	
lab2C.exe: lab2C.obj
	tlink /v lab2C

lab2C.obj: lab2C.asm
	tasm /zi lab2C.asm ,, lab2C.lst
	
lab2D.exe: lab2D.obj
	tlink /v lab2D

lab2D.obj: lab2D.asm
	tasm /zi lab2D.asm ,, lab2D.lst
	
	
lab2E.exe: lab2E.obj
	tlink /v lab2E

lab2E.obj: lab2E.asm
	tasm /zi lab2E.asm ,, lab2E.lst

